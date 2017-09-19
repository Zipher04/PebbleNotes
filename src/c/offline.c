
#include "pebble.h"
#include "offline.h"
#include "misc.h"
#include "consts.h"
#include "tasks.h"
#include "isoTime.h"

static const int c_task_shift_size = PERSIST_TASK_END - PERSIST_TASK_ID_0;
static const int c_list_length_max = 200 / ( PERSIST_TASK_END - PERSIST_TASK_ID_0 );

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
	for ( int taskId = 0; taskId < taskCount; ++taskId )
	{
		offline_get_task_title( taskId, title, titleLengthMax );
		offline_get_task_note( taskId, note, noteLengthMax );
		ts_set_item( taskId, ( TS_Item )
		{
			.id = taskId,
				.done = offline_get_task_status( taskId ),
				.title = title,
				.notes = note,
		} );
	}
	return;
}

/**
 *
 */
void offline_set_list_id( char* id )
{
	int byteWriten = persist_write_string( PERSIST_LIST_ID, id );
	assert( byteWriten > 0, "persist write failed." );
}
void offline_get_list_id( char* id, int length )
{
	if ( !persist_exists( PERSIST_LIST_ID ) )
	{
		LOG( "List id not found." );
		id[0] = '\0';
	}
	assert( length > persist_get_size( PERSIST_LIST_ID ), "Length for list id too small" );
	persist_read_string( PERSIST_LIST_ID, id, length );
}

/**
 * Number of tasks inside list
 */
void offline_set_list_length( int length )
{
	assert( length < c_list_length_max, "list length too large" );
	int byteWriten = persist_write_int( PERSIST_LIST_LENGTH, length );
	assert( byteWriten > 0, "persist write failed." );
}
int offline_get_list_length( void )
{
	//will be 0 if not set
	return persist_read_int( PERSIST_LIST_LENGTH );
}

/**
 *
 */
void offline_set_list_sync_time( char* time )
{
	int byteWriten = persist_write_string( PERSIST_LIST_SYNC_TIME, time );
	assert( byteWriten > 0, "persist write failed." );
}
void offline_get_list_sync_time( char* time, int length )
{
	assert( length > 0, "length < 0" );
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
	int byteWriten = persist_write_string( i*c_task_shift_size + PERSIST_TASK_ID_0, id );
	assert( byteWriten > 0, "persist write failed." );
}
void offline_get_task_id( int i, char* id, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_ID_0;
	assert( length > 0, "Length <= 0" );
	if ( !persist_exists( target ) )
	{
		id[0] = '\0';
		return;
	}
	assert( length > persist_get_size( target ), "Length for task id too small" );
	persist_read_string( target, id, length );
}

/**
 *
 */
void offline_set_task_title( int i, char* title )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	int byteWriten = persist_write_string( i*c_task_shift_size + PERSIST_TASK_TITLE_0, title );
	assert( byteWriten > 0, "persist write failed." );
}
void offline_get_task_title( int i, char* title, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_TITLE_0;
	assert( length > 0, "Length <= 0" );
	if ( !persist_exists( target ) )
	{
		title[0] = '\0';
		return;
	}
	assert( length > persist_get_size( target ), "Length for task title too small" );
	persist_read_string( target, title, length );
}

/**
 *
 */
void offline_set_task_note( int i, char* note )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	int byteWriten = persist_write_string( i*c_task_shift_size + PERSIST_TASK_NOTE_0, note );
	assert( byteWriten > 0, "persist write failed." );
}
void offline_get_task_note( int i, char* note, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_NOTE_0;
	assert( length > 0, "Length <= 0" );
	if ( !persist_exists( target ) )
	{
		note[0] = '\0';
		return;
	}
	assert( length > persist_get_size( target ), "Length for task note too small" );
	persist_read_string( target, note, length );
}

/**
 * @para done: 0:unchecked, 1:checked
 */
void offline_set_task_status( int i, int done )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	int byteWriten = persist_write_int( i*c_task_shift_size + PERSIST_TASK_DONE_0, done );
	assert( byteWriten > 0, "persist write failed." );
}
int offline_get_task_status( int i )
{
	return persist_read_int( i*c_task_shift_size + PERSIST_TASK_DONE_0 );
}

/**
 *
 */
void offline_set_task_update_time( int i, char* time )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_UPDATE_TIME_0;
	int byteWriten = persist_write_string( target, time );
	assert( byteWriten > 0, "persist write failed." );
}

void offline_update_task_update_time( int i )
{
	char time[30];
	GetIsoTime( time, 30 );
	offline_set_task_update_time( i, time );
}

void offline_get_task_update_time( int i, char* time, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_UPDATE_TIME_0;
	assert( persist_exists( target ), "Read task with invalid index" );
	assert( length > persist_get_size( target ), "Length for task time too small" );
	persist_read_string( target, time, length );
}

void offline_remove_task( int index )
{
	int length = offline_get_list_length();
	assert( index < length, "Invalid index for task removing!" );
	enum
	{
		ID_SIZE = 50,
		TITLE_SIZE = 50,
		NOTES_SIZE = 50,
		TIME_SIZE = 50,
	};
	char id[ID_SIZE], title[TITLE_SIZE], notes[NOTES_SIZE], time[TIME_SIZE];
	int status;

	for ( int i = index ; i < length - 1 ; ++i )
	{
		offline_get_task_id( i + 1, id, ID_SIZE );
		offline_set_task_id( i, id );

		offline_get_task_title( i + 1, title, TITLE_SIZE );
		offline_set_task_title( i, title );

		offline_get_task_note( i + 1, notes, NOTES_SIZE );
		offline_set_task_note( i, notes );

		status = offline_get_task_status( i + 1 );
		offline_set_task_status( i, status );

		offline_get_task_update_time( i + 1, time, TIME_SIZE );
		offline_set_task_update_time( i, time );
	}
	offline_set_list_length( length - 1 );
}