
#include "pebble.h"
#include "persist.h"
#include "offline.h"
#include "misc.h"
#include "tasklists.h"
#include "tasks.h"

int offline_read_lists( void )
{
	int listCount = -1;
	
	persist_read_list_count( &listCount );
	if ( listCount <= 0 )
	{	
		LOG( "offline: read list count < 0" );
	}
	tl_set_count( listCount );
	
	const int titleLengthMax = 30;
	char title[titleLengthMax];
	for ( int listId = 0 ; listId < listCount ; ++listId )
	{
		persist_read_list( listId, title, titleLengthMax );
		tl_set_item( listId, (TL_Item){
				.id = listId,
				.title = title,
			});
	}
	return 0;
}

int offline_read_tasks( int listId )
{
	int taskCount = -1;
	
	persist_read_task_count( listId, &taskCount );
	if ( taskCount <= 0 )
	{	
		LOG( "offline: read task count < 0" );
	}
	ts_set_count( taskCount );
	const int titleLengthMax  = 30;
	char title[titleLengthMax];
	int done;
	for ( int taskId = 0 ; taskId < taskCount ; ++taskId )
	{
		persist_read_task( listId, taskId, title, titleLengthMax, &done );
		ts_set_item( taskId, (TS_Item){
				.id = taskId,
				.done = done,
				.title = title,
				.notes = "",
			});
	}
	return 0;
}