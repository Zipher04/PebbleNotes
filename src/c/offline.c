
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
	int taskCount = PersistGetListLength();

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
		PersistGetTaskTitle( taskId, title, titleLengthMax );
		PersistGetTaskNotes( taskId, note, noteLengthMax );
		ts_set_item( taskId, ( TS_Item )
		{
			.id = taskId,
				.done = PersistGetTaskStatus( taskId ),
				.title = title,
				.notes = note,
		} );
	}
	return;
}

/**
 *
 */
void PersisitSetListId( char* id )
{
	int byteWriten = persist_write_string( PERSIST_LIST_ID, id );
	assert( byteWriten > 0, "persist write failed." );
}
void PersisitGetListId( char* id, int length )
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
void PersistSetListLength( int length )
{
	assert( length < c_list_length_max, "list length too large" );
	int byteWriten = persist_write_int( PERSIST_LIST_LENGTH, length );
	assert( byteWriten > 0, "persist write failed." );
}
int PersistGetListLength( void )
{
	//will be 0 if not set
	return persist_read_int( PERSIST_LIST_LENGTH );
}

/**
 *
 */
void PersistSetListSyncTime( char* time )
{
	int byteWriten = persist_write_string( PERSIST_LIST_SYNC_TIME, time );
	assert( byteWriten > 0, "persist write failed." );
}
void PersistGetListSyncTime( char* time, int length )
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
void PersistSetTaskId( int i, char* id )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	int byteWriten = persist_write_string( i*c_task_shift_size + PERSIST_TASK_ID_0, id );
	assert( byteWriten > 0, "persist write failed." );
}
void PersistGetTaskId( int i, char* id, int length )
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
void PersistSetTaskTitle( int i, char* title )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	int byteWriten = persist_write_string( i*c_task_shift_size + PERSIST_TASK_TITLE_0, title );
	assert( byteWriten > 0, "persist write failed." );
}
void PersistGetTaskTitle( int i, char* title, int length )
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
void PersistSetTaskNotes( int i, char* note )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	int byteWriten = persist_write_string( i*c_task_shift_size + PERSIST_TASK_NOTE_0, note );
	assert( byteWriten > 0, "persist write failed." );
}
void PersistGetTaskNotes( int i, char* note, int length )
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
void PersistSetTaskStatus( int i, int done )
{
	assert( i < c_list_length_max && i >= 0, "Invalid task index" );
	int byteWriten = persist_write_int( i*c_task_shift_size + PERSIST_TASK_DONE_0, done );
	assert( byteWriten > 0, "persist write failed." );
}
int PersistGetTaskStatus( int i )
{
	return persist_read_int( i*c_task_shift_size + PERSIST_TASK_DONE_0 );
}

/**
 *
 */
void PersistSetTaskUpdateTime( int i, char* time )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_UPDATE_TIME_0;
	int byteWriten = persist_write_string( target, time );
	assert( byteWriten > 0, "persist write failed." );
}

void PersistUpdateTaskUpdateTime( int i )
{
	char time[30];
	GetIsoTime( time, 30 );
	PersistSetTaskUpdateTime( i, time );
}

void PersistGetTaskUpdateTime( int i, char* time, int length )
{
	const int target = i*c_task_shift_size + PERSIST_TASK_UPDATE_TIME_0;
	assert( persist_exists( target ), "Read task with invalid index" );
	assert( length > persist_get_size( target ), "Length for task time too small" );
	persist_read_string( target, time, length );
}

void PersistRemoveTask( int index )
{
	int length = PersistGetListLength();
	assert( index < length, "Invalid index for task removing!" );
	
	char id[SIZE_TASK_ID], title[SIZE_TASK_TITLE], notes[SIZE_TASK_NOTE], time[SIZE_TIME];
	int status;

	for ( int i = index ; i < length - 1 ; ++i )
	{
		PersistGetTaskId( i + 1, id, SIZE_TASK_ID );
		PersistSetTaskId( i, id );

		PersistGetTaskTitle( i + 1, title, SIZE_TASK_TITLE );
		PersistSetTaskTitle( i, title );

		PersistGetTaskNotes( i + 1, notes, SIZE_TASK_NOTE );
		PersistSetTaskNotes( i, notes );

		status = PersistGetTaskStatus( i + 1 );
		PersistSetTaskStatus( i, status );

		PersistGetTaskUpdateTime( i + 1, time, SIZE_TIME );
		PersistSetTaskUpdateTime( i, time );
	}
	PersistSetListLength( length - 1 );
}