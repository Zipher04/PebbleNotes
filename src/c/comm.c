#include <pebble.h>
#include "comm.h"
#include "misc.h"
#include "consts.h"
#include "tasklists.h"
#include "tasks.h"
#include "taskinfo.h"
#include "statusbar.h"
#include "options.h"
#include "persist.h"
#include "offline.h"

static bool comm_js_ready = false;	//ready from js received
static CommJsReadyCallback comm_js_ready_cb;
static void *comm_js_ready_cb_data;
static int comm_array_size = -1;
static int g_comm_last_query_listId = -1;
static int gTaskSendingIndex = -1;

static bool comm_is_bluetooth_available() {
	if(!bluetooth_connection_service_peek()) {
		sb_show("No bluetooth connection!");
		return false;
	}
	return true;
}
bool comm_is_available() {
	if(!comm_is_bluetooth_available())
		return false;
	if(!comm_js_ready) {
		sb_show("JS not available, please try again later");
		return false;
	}
	return true;
}
bool comm_is_available_silent() {
	return bluetooth_connection_service_peek() && comm_js_ready;
}

void comm_query_tasklists_cb(void *arg) {
	comm_query_tasklists();
}
void comm_query_tasklists() {
	if ( !comm_is_bluetooth_available() )
	{
		offline_read_lists();
		sb_show( "offline lists" );
		return;
	}
	if(!comm_js_ready) {
		comm_js_ready_cb = comm_query_tasklists_cb;
		sb_show("Waiting for JS...");
		comm_is_bluetooth_available(); // check bluetooth connection and show message if needed
		return;
	}
	if(!comm_is_available())
	{
		return;
	}
	sb_show("Connecting...");
	LOG("Querying tasklists");
	DictionaryIterator *iter;
	Tuplet code = TupletInteger(KEY_CODE, CODE_GET);
	Tuplet scope = TupletInteger(KEY_SCOPE, SCOPE_LISTS);

	app_message_outbox_begin(&iter);
	dict_write_tuplet(iter, &code);
	dict_write_tuplet(iter, &scope);
	app_message_outbox_send();
}
void comm_query_tasks_cb(void *arg) {
	comm_query_tasks((int)arg);
}
void comm_query_tasks(int listId) {
	if ( !comm_is_bluetooth_available() )
	{
		offline_read_tasks( listId );
		sb_show( "offline tasks" );
		return;
	}
	if(!comm_js_ready) {
		comm_js_ready_cb = comm_query_tasks_cb;
		comm_js_ready_cb_data = (void*)listId;
		comm_is_available(); // show message if needed
		return;
	}
	g_comm_last_query_listId = listId;
	if(!comm_is_available())
	{
		return;
	}
	sb_show("Connecting...");
	LOG("Querying tasks for listId=%d", listId);
	DictionaryIterator *iter;
	Tuplet code = TupletInteger(KEY_CODE, CODE_GET);
	Tuplet scope = TupletInteger(KEY_SCOPE, SCOPE_TASKS);
	Tuplet tListId = TupletInteger(KEY_LISTID, listId);

	app_message_outbox_begin(&iter);
	dict_write_tuplet(iter, &code);
	dict_write_tuplet(iter, &scope);
	dict_write_tuplet(iter, &tListId);
	app_message_outbox_send();
}
void comm_query_task_details(int listId, int taskId) {
	LOG("Querying task details for %d, %d (not implemented)", listId, taskId);
}

void comm_update_task_status(int listId, int taskId, bool newStatus) {
	if(!comm_is_available())
		return;
	LOG("Updating status for task %d->%d to %d (NI)", listId, taskId, newStatus);
	sb_show("Updating...");
	DictionaryIterator *iter;
	Tuplet code = TupletInteger(KEY_CODE, CODE_UPDATE);
	Tuplet scope = TupletInteger(KEY_SCOPE, SCOPE_TASK);
	Tuplet tListId = TupletInteger(KEY_LISTID, listId);
	Tuplet tTaskId = TupletInteger(KEY_TASKID, taskId);
	Tuplet tIsDone = TupletInteger(KEY_ISDONE, newStatus);

	app_message_outbox_begin(&iter);
	dict_write_tuplet(iter, &code);
	dict_write_tuplet(iter, &scope);
	dict_write_tuplet(iter, &tListId);
	dict_write_tuplet(iter, &tTaskId);
	dict_write_tuplet(iter, &tIsDone);
	app_message_outbox_send();
}

void comm_create_task(int listId, char* title, char* notes) {
	if(!comm_is_available()) {
		// TODO: alert?
		return;
	}
	LOG("Creating new task with title %s in list %d", title, listId);
	sb_show("Creating...");
	DictionaryIterator *iter;
	Tuplet code = TupletInteger(KEY_CODE, CODE_POST);
	Tuplet scope = TupletInteger(KEY_SCOPE, SCOPE_TASK);
	Tuplet tListId = TupletInteger(KEY_LISTID, listId);
	Tuplet tTitle = TupletCString(KEY_TITLE, title);

	app_message_outbox_begin(&iter);
	dict_write_tuplet(iter, &code);
	dict_write_tuplet(iter, &scope);
	dict_write_tuplet(iter, &tListId);
	dict_write_tuplet(iter, &tTitle);
	if(notes) {
		Tuplet tNotes = TupletCString(KEY_NOTES, notes);
		dict_write_tuplet(iter, &tNotes);
	}
	app_message_outbox_send();
}

void SentListToPhone( void ) {
	LOG ( "Sending list" );
	
	int listLength = offline_get_list_length();
		
	char id[35], syncTime[26];
	offline_get_list_id( id, 35 );
	offline_get_list_sync_time( syncTime, 26 );
	
	DictionaryIterator *iter;
	Tuplet tCode = TupletInteger( KEY_CODE, CODE_SEND_LIST );
	Tuplet tId = TupletCString( KEY_ID, &id[0] );
	Tuplet tLength = TupletInteger( KEY_LENGTH, listLength );
	Tuplet tSyncTime = TupletCString( KEY_UPDATED, &syncTime[0] );
	

	int result = app_message_outbox_begin(&iter);
	assert( APP_MSG_OK == result, "Error: outbox failed" );
	dict_write_tuplet(iter, &tCode);
	dict_write_tuplet(iter, &tId );
	dict_write_tuplet(iter, &tLength );
	dict_write_tuplet(iter, &tSyncTime );
	app_message_outbox_send();
}

void SentTaskToPhone( int taskIndex ) 
{
	char id[SIZE_TASK_ID], title[SIZE_TASK_TITLE], note[SIZE_TASK_NOTE], updateTime[SIZE_TIME];
			
	offline_get_task_id( taskIndex, id, SIZE_TASK_ID );
	offline_get_task_title( taskIndex, title, SIZE_TASK_TITLE );
	offline_get_task_note( taskIndex, note, SIZE_TASK_NOTE );
	offline_get_task_update_time( taskIndex, updateTime, SIZE_TIME );
	
	DictionaryIterator *iter;
	Tuplet tCode = TupletInteger( KEY_CODE, CODE_SEND_TASK );
	Tuplet tId = TupletCString( KEY_ID, &id[0] );
	Tuplet tTitle = TupletCString( KEY_TITLE, &title[0] );
	Tuplet tNote = TupletCString( KEY_NOTE, &note[0] );
	Tuplet tUpdateTime = TupletCString( KEY_UPDATED, &updateTime[0] );
	
	int result = app_message_outbox_begin(&iter);
	assert( APP_MSG_OK == result, "Error: outbox failed" );
	dict_write_tuplet(iter, &tCode);
	dict_write_tuplet(iter, &tId );
	dict_write_tuplet(iter, &tTitle);
	dict_write_tuplet(iter, &tNote);
	dict_write_tuplet(iter, &tUpdateTime );
	app_message_outbox_send();
}

void SendCodeToPhone( int code )
{
	DictionaryIterator *iter;
	int result = app_message_outbox_begin(&iter);
	assert( APP_MSG_OK == result, "Error: outbox failed" );
	Tuplet tCode = TupletInteger( KEY_CODE, code );
	dict_write_tuplet( iter, &tCode );
	app_message_outbox_send();
	return;		
}

// Send saved "refresh token" and "access token" if possible
void comm_retrieve_tokens() {
	// loading
	char *szAccessToken = NULL, *szRefreshToken = NULL;
	int size;
	if(persist_exists(PERSIST_REFRESH_TOKEN)) { // use the same keys for appMessage and for storage
		size = persist_get_size(PERSIST_REFRESH_TOKEN);
		szRefreshToken = malloc(size);
		persist_read_string(PERSIST_REFRESH_TOKEN, szRefreshToken, size);
		LOG("got refresh token: %s", szRefreshToken);

		if(persist_exists(PERSIST_ACCESS_TOKEN)) { // only try access token if we have refresh token, as AT alone is not useful
			size = persist_get_size(PERSIST_ACCESS_TOKEN);
			szAccessToken = malloc(size);
			persist_read_string(PERSIST_ACCESS_TOKEN, szAccessToken, size);
			LOG("got access token: %s", szRefreshToken);
		}
	}

	// sending
	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);
	Tuplet code = TupletInteger(KEY_CODE, CODE_RETRIEVE_TOKEN);
	dict_write_tuplet(iter, &code);
	if(szAccessToken) {
		Tuplet tAccessToken = TupletCString(KEY_ACCESS_TOKEN, szAccessToken);
		dict_write_tuplet(iter, &tAccessToken);
	}
	if(szRefreshToken) {
		Tuplet tRefreshToken = TupletCString(KEY_REFRESH_TOKEN, szRefreshToken);
		dict_write_tuplet(iter, &tRefreshToken);
	}
	app_message_outbox_send();

	if(szAccessToken)
		free(szAccessToken);
	if(szRefreshToken)
		free(szRefreshToken);
}

static void comm_in_received_handler(DictionaryIterator *iter, void *context) {
	Tuple *tCode, *tMessage, *tScope;

	LOG("Used: %d, free: %d", heap_bytes_used(), heap_bytes_free());

	tCode = dict_find(iter, KEY_CODE);
	assert(tCode, "Message without code");
	int code = (int)tCode->value->int32;
	LOG("Message code: %d", code);

	if(code == CODE_ERROR) {
		tMessage = dict_find(iter, KEY_ERROR);
		char* message = "Unknown error";
		if(tMessage && tMessage->type == TUPLE_CSTRING)
			message = tMessage->value->cstring;
		LOG("Error received: %s", message);
		sb_show(message);
		return;
	} else if(code == CODE_SAVE_TOKEN) { // JS wants to save token
		LOG("Saving tokens");
		Tuple *tAccessToken = dict_find(iter, KEY_ACCESS_TOKEN);
		if(tAccessToken && tAccessToken->type == TUPLE_CSTRING)
			persist_write_string(PERSIST_ACCESS_TOKEN, tAccessToken->value->cstring); // use the same key for storage as for appMessage
		else // if no token was passed, assume logout - delete saved token
			persist_delete(PERSIST_ACCESS_TOKEN);

		Tuple *tRefreshToken = dict_find(iter, KEY_REFRESH_TOKEN);
		if(tRefreshToken && tRefreshToken->type == TUPLE_CSTRING)
			persist_write_string(PERSIST_REFRESH_TOKEN, tAccessToken->value->cstring);
		else
			persist_delete(PERSIST_REFRESH_TOKEN);

		return;
	} else if(code == CODE_RETRIEVE_TOKEN) { // JS requires saved token
		LOG("Retrieving tokens");
		comm_retrieve_tokens();
		return;
	} else if(code == CODE_SET_OPTION) {
		LOG("Updating option");
		Tuple *tOptionId = dict_find(iter, KEY_OPTION_ID);
		Tuple *tOptionVal = dict_find(iter, KEY_OPTION_VALUE);
		options_update(tOptionId->value->int32, tOptionVal->value->int32);
		return;
	} else if( code == CODE_READY ) { // JS just loaded
		comm_js_ready = true;
		if( comm_js_ready_cb ) {
			LOG("JS Ready Callback awaiting, calling");
			comm_js_ready_cb(comm_js_ready_cb_data);
		}
		sb_show("Syncing...");
		SentListToPhone();
		SentTasksToPhone();
		return;
	} else if( code == CODE_SEND_LIST_ACK ) {
		if ( 0 == offline_get_list_length() )
		{
			SendCodeToPhone( CODE_SYNC_LIST );
		}
		else
		{
			SentTaskToPhone( 0 );
			gTaskSendingIndex = 1;
		}
		return;
	} else if ( CODE_SEND_TASK_ACK == code ) {
		if ( gTaskSendingIndex >= offline_get_list_length() )
		{
			SendCodeToPhone( CODE_SEND_TASK_END );
		}
		else 
		{
			SentTaskToPhone( gTaskSendingIndex++ );
		}
		return;
	} else if ( CODE_SEND_TASK_END_ACK == code ) {
		SendCodeToPhone( CODE_SYNC_LIST );
	}


	tScope = dict_find(iter, KEY_SCOPE);
	assert(tScope, "No scope!");
	int scope = (int)tScope->value->int32;
	LOG("Message scope: %d", scope);

	if(scope == SCOPE_LISTS) {
		// this might be legal if we auto-switched to the only list
		//assert(tl_is_active(), "Ignoring TaskLists-related message because that list is inactive");
	} else if(scope == SCOPE_TASKS) {
		assert(ts_is_active(), "Ignoring Tasks-related message because tasks is inactive");
	} else if(scope == SCOPE_TASK) {
		assert(ts_is_active()||ti_is_active(), "Ignoring Task-related message because neither tasks nor taskinfo is inactive");
	} else {
		APP_LOG(APP_LOG_LEVEL_ERROR, "Unexpected scope: %d", scope);
		return;
	}

	if(code == CODE_ARRAY_START) {
		int count = (int)dict_find(iter, KEY_COUNT)->value->int32;
		LOG("Items count: %d", count);
		comm_array_size = count;
		if(scope == SCOPE_LISTS) {
			tl_set_count(count);
			persist_write_list_count(count);
		} else if(scope == SCOPE_TASKS) {
			ts_set_count(count);
			persist_write_task_count( g_comm_last_query_listId, count );
		} else LOG("Err!");
		snprintf(sb_printf_alloc(32), 32, "Loading...");
		sb_printf_update();
	} else if(code == CODE_ARRAY_ITEM) {
		assert(comm_array_size > 0, "Unexpected array_item!");
		int i = (int)dict_find(iter, KEY_ITEM)->value->int32;
		assert(i < comm_array_size, "Index %d exceeds size %d", i, comm_array_size);
		snprintf(sb_printf_get(), 32, "Loading... %d%%", 100 * (i+1) / comm_array_size);
		sb_printf_update();
		LOG("Statusbar Updated: %d", 100 * (i+1) / comm_array_size);
		char *title = dict_find(iter, KEY_TITLE)->value->cstring;
		if(scope == SCOPE_LISTS) {
			int listId = (int)dict_find(iter, KEY_LISTID)->value->int32;
			LOG("Item No: %d, Id=%d", i, listId);
			tl_set_item(i, (TL_Item){
				.id = listId,
				.title = title,
			});
			//persist_write_list( listId, title );
		} else {
			// TODO: check listId?
			int taskId = (int)dict_find(iter, KEY_TASKID)->value->int32;
			Tuple *tNotes = dict_find(iter, KEY_NOTES);
			char *notes = NULL;
			if(tNotes)
				notes = tNotes->value->cstring;
			bool isDone = (bool)dict_find(iter, KEY_ISDONE)->value->int32;
			LOG("Item No: %d, Id=%d, done=%d", i, taskId, isDone);
			ts_set_item(i, (TS_Item){
				.id = taskId,
				.done = isDone,
				.title = title,
				.notes = notes,
			});
			persist_write_task( g_comm_last_query_listId, taskId, title, isDone );
		}
	} else if(code == CODE_ITEM_UPDATED) {
		assert(scope == SCOPE_TASK, "Unexpected scope %d, expected TASK", scope);
		int listId = (int)dict_find(iter, KEY_LISTID)->value->int32;
		assert(listId == ts_current_listId(), "Ignoring message for non-current listId %d, current is %d", listId, ts_current_listId());
		int taskId = (int)dict_find(iter, KEY_TASKID)->value->int32;
		bool isDone = (bool)dict_find(iter, KEY_ISDONE)->value->int32;
		LOG("List id: %d, Item id: %d, New status: %d", listId, taskId, isDone);
		ts_update_item_state_by_id(taskId, isDone);
		sb_hide(); // hide "Updating" message
	} else if(code == CODE_ITEM_ADDED) {
		assert(scope == SCOPE_TASKS, "Unexpected scope %d, expected TASKS", scope);
		int listId = (int)dict_find(iter, KEY_LISTID)->value->int32;
		assert(listId == ts_current_listId(), "Ignoring message for non-current listId %d, current is %d", listId, ts_current_listId());
		int taskId = (int)dict_find(iter, KEY_TASKID)->value->int32;
		char *title = dict_find(iter, KEY_TITLE)->value->cstring;
		Tuple *tNotes = dict_find(iter, KEY_NOTES);
		char *notes = NULL;
		if(tNotes)
			notes = tNotes->value->cstring;
		bool isDone = (bool)dict_find(iter, KEY_ISDONE)->value->int32;
		LOG("Item Id=%d, done=%d", taskId, isDone);
		ts_append_item((TS_Item){
			.id = taskId,
			.done = isDone,
			.title = title,
			.notes = notes,
		});
		sb_hide(); // hide "Creating" message
	} else if(code == CODE_ARRAY_END) {
		comm_array_size = -1; // no current array
		sb_hide(); // hide load percentage
		ts_show_pebble();
	} else if ( CODE_SEND_LIST == code ) {
		char *id = dict_find( iter, KEY_ID )->value->cstring;
		offline_set_list_id( id );
		int length = dict_find( iter, KEY_LENGTH )->value->int32;
		offline_set_list_length( length );
		char *updated = dict_find( iter, KEY_UPDATED )->value->cstring;
		offline_set_list_sync_time( updated );
		comm_array_size = length;
		sb_show( "Loading task from phone..." );
	} else if ( CODE_SEND_TASK_START == code ) {
		
	} else if ( CODE_SEND_TASK == code ) {
		assert( comm_array_size > 0, "Unexpected array_item!" );
		int i = (int)dict_find( iter, KEY_ITEM )->value->int32;
		assert( i < comm_array_size, "Index %d exceeds size %d", i, comm_array_size);
		snprintf( sb_printf_get(), 32, "Loading... %d%%", 100 * (i+1) / comm_array_size );
		sb_printf_update();
		LOG("Statusbar Updated: %d", 100 * (i+1) / comm_array_size );
		
		int  item = dict_find( iter, KEY_ITEM	)->value->int32;
		char *id 	= dict_find( iter, KEY_ID	)->value->cstring;
		char *title = dict_find( iter, KEY_TITLE)->value->cstring;
		char *note 	= dict_find( iter, KEY_NOTE	)->value->cstring;
		int  done 	= dict_find( iter, KEY_DONE	)->value->int32;
		char *updated = dict_find( iter, KEY_UPDATED )->value->cstring;
		
		LOG("Item No %d: Id=%s, title=%s, note=%s, done=%d, updated=%s", i, id, title, note, done, updated );
		
		offline_set_task_id( item, id );
		offline_set_task_title( item, title );
		offline_set_task_note( item, note );
		offline_set_task_done( item, done );
		offline_set_task_update_time( item, updated );
	} else if ( CODE_SEND_TASK_END == code ) {
		comm_array_size = -1; // no current array
		sb_hide(); // hide load percentage
		ts_show_pebble();
	} else {
		LOG("Unexpected message code: %d", code);
	}
}
static void comm_in_dropped_handler(AppMessageResult reason, void *context) {
	LOG("Message dropped: reason=%d", reason);
}
static void comm_out_sent_handler(DictionaryIterator *sent, void *context) {
	LOG("Message sent");
}
static void comm_out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
	LOG("Message send failed: reason=%d", reason);
}
void comm_init() {
	app_message_register_inbox_received(comm_in_received_handler);
	app_message_register_inbox_dropped(comm_in_dropped_handler);
	app_message_register_outbox_sent(comm_out_sent_handler);
	app_message_register_outbox_failed(comm_out_failed_handler);

	app_message_open(MIN(app_message_inbox_size_maximum(), INBOX_DESIRED_MAX), APP_MESSAGE_OUTBOX_SIZE_MINIMUM); // We only need large buffer for inbox
}
void comm_deinit() {
	app_message_deregister_callbacks();
}


//==========================================================
// Watch send
//==========================================================

void TrySyncWithPhone( void ) {
	if ( !comm_is_bluetooth_available() )
	{
		//offline_read_list_pebble();
		LOG( "offline mode" );
		ts_show_pebble();
		return;
	}
	if( !comm_js_ready ) {
		comm_is_available(); // show message if needed
		return;
	}
}
