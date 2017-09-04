
#include <string.h>
#include "pebble.h"
#include "consts.h"
#include "misc.h"
#include "persist.h"

int persist_get_task_count_key( int listId )
{
	return 0;
}

int persist_write_list_count( int count )
{
	return 0;
}

int persist_write_task_count( int listId, int count )
{
	int key = persist_get_task_count_key( listId );
	if ( key <= 0 )
	{
		LOG("Persist: cannot found key for task count");
		return -1;
	}
	persist_write_int( key, count );
	LOG( "Persist: write %d: %d", key, count );
	return 0;
}

int persist_write_list( int listId, char* title )
{
	
	return 0;
}

int persist_write_task( int listId, int taskId, char* title, int done )
{
	LOG( "Persist: write called with %d,%d: %s", listId, taskId, title );
	int key = persist_get_task_count_key( listId );
	if ( key <= 0 )
	{
		LOG("Persist: cannot found key for task count");
		return -1;
	}
	LOG( "Persist: key to write: %d", key+taskId+1 );
	int sizeString = strlen( title ) + 2;
	char* string = malloc(sizeString);
	string[0] = done ? '1' : '0';
	strcpy( string+1, title);
	LOG( "Persist: string to write: %s", string );
	persist_write_string( key+taskId+1, string );
	free( string );
	LOG( "Persist: write %d: %s", key+taskId+1, string );
	return 0;
}

int persist_read_list_count( int *count )
{
	
	return 0;
}

int persist_read_task_count( int listId, int *count )
{
	int key = persist_get_task_count_key( listId );
	if ( !persist_exists( key ) )
	{
		LOG("Persist: Task count for listId %d not defined.", listId );
		return -1;
	}
	*count = persist_read_int( key );
	return 0;
}

int persist_read_list( int listId, char* title, int sizeTitle )
{
	
	return 0;
}

int persist_read_task( int listId, int taskId, char* title, int sizeTitle, int *done )
{
	int key = persist_get_task_count_key( listId ) + 1 + taskId;
	if ( !persist_exists( key ) )
	{
		LOG("Persist: reading not existing task");
		return -1;
	}
	const int sizeString = sizeTitle + 2;
	char *string = malloc( sizeString );
	persist_read_string( key, string, sizeString );
	*done = string[0] == '1';
	strncpy( title, string+1, sizeTitle );
	free( string );
	return 0;
}
