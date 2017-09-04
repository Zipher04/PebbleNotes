
#include "pebble.h"
#include "offline.h"
#include "misc.h"
#include "consts.h"
#include "tasks.h"

static const int c_task_shift_size = PERSIST_TASK_END - PERSIST_TASK_ID_0;
static const int c_list_length_max = 200 / (PERSIST_TASK_END - PERSIST_TASK_ID_0);

int offline_read_lists( void )
{
	return 0;
}

int offline_read_tasks( int listId )
{
	return 0;
}

void offline_read_list_pebble( void )
{
	int taskCount = offline_get_list_length();
	
	if ( taskCount <= 0 )
	{	
		return;
	}
	ts_set_count( taskCount );
	const int titleLengthMax = 30;
	const int noteLengthMax = 30;
	char title[titleLengthMax], note[noteLengthMax];
	for ( int taskId = 0 ; taskId < taskCount ; ++taskId )
	{
		offline_get_task_title( taskId, title, titleLengthMax );
		offline_get_task_note( taskId, note, noteLengthMax );
		ts_set_item( taskId, (TS_Item){
				.id = taskId,
				.done = offline_is_task_done( taskId),
				.title = title,
				.notes = note,
			});
	}
	return;
}

/**
 * 
 */
void offline_set_list_id( char* id )
{
	persist_write_string( PERSIST_LIST_ID, id );
}
void offline_get_list_id( char* id, int length )
{
	assert( persist_exists( PERSIST_LIST_ID ), "List id not exist" );
	assert( length > persist_get_size( PERSIST_LIST_ID ), "Length for list id too small" );
	persist_read_string( PERSIST_LIST_ID, id, length );
}

/**
 * Number of tasks inside list
 */
void offline_set_list_length( int length )
{
	assert( length < c_list_length_max, "list length too large" );
	persist_write_int( PERSIST_LIST_LENGTH, length );
}
int offline_get_list_length( void )
{
	//will be 0 if not set
	return persist_read_int( PERSIST_LIST_LENGTH );
}

/**
 * Set list is modified. Will be checked before sync.
 */
void offline_set_list_modified( int modified )
{
	persist_write_int( PERSIST_LIST_MODIFIED, modified );
}
int offline_is_list_modified( void )
{
	return persist_read_int( PERSIST_LIST_MODIFIED ) == 0 ? 0 : 1;
}

/**
 * 
 */
void offline_set_list_sync_time( char* time )
{
	persist_write_string( PERSIST_LIST_SYNC_TIME, time );
}
void offline_get_list_sync_time( char* time, int length )
{
	assert( length > 0 , "length < 0" );
	if ( !persist_exists( PERSIST_LIST_SYNC_TIME ) )
	{
		time[0] = '\0';
		return;
	}
	assert( length > persist_get_size( PERSIST_LIST_SYNC_TIME ), "Length for time too small" );
	persist_read_string( PERSIST_LIST_SYNC_TIME, time, length );
}
 
/**
 * 
 */
void offline_set_task_id( int i, char* id )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	persist_write_string( i*c_task_shift_size + PERSIST_TASK_ID_0, id );
}
void offline_get_task_id( int i, char* id, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_ID_0;
	assert( persist_exists(target), "Read task with invalid index" );
	assert( length > persist_get_size( target ), "Length for task id too small" );
	persist_read_string( target, id, length );
}
 
/**
 * 
 */
void offline_set_task_title( int i, char* title )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	persist_write_string( i*c_task_shift_size + PERSIST_TASK_TITLE_0, title );
}
void offline_get_task_title( int i, char* title, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_TITLE_0;
	assert( persist_exists(target), "Read task with invalid index" );
	assert( length > persist_get_size( target ), "Length for task title too small" );
	persist_read_string( target, title, length );
}
 
/**
 * 
 */
void offline_set_task_note( int i, char* note )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	persist_write_string( i*c_task_shift_size + PERSIST_TASK_NOTE_0, note );
}
void offline_get_task_note( int i, char* note, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_NOTE_0;
	assert( persist_exists(target), "Read task with invalid index" );
	assert( length > persist_get_size( target ), "Length for task note too small" );
	persist_read_string( target, note, length );
}
 
/**
 * @para done: 0:unchecked, 1:checked
 */
void offline_set_task_done( int i, int done )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	persist_write_int( i*c_task_shift_size + PERSIST_TASK_DONE_0, done == 0 ? 0 : 1 );
}
int offline_is_task_done( int i )
{
	return persist_read_int( i*c_task_shift_size + PERSIST_TASK_DONE_0 ) == 0 ? 0 : 1;
}

/**
 * 
 */
void offline_set_task_update_time( int i, char* time )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_UPDATE_TIME_0;
	persist_write_string( target, time );
}
void offline_get_task_update_time( int i, char* time, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_UPDATE_TIME_0;
	assert( persist_exists(target), "Read task with invalid index" );
	assert( length > persist_get_size( target ), "Length for task time too small" );
	persist_read_string( target, time, length );
}
