
#include <string.h>
#include "pebble.h"
#include "consts.h"
#include "misc.h"
#include "persist.h"

int persist_get_task_count_key( int listId )
{
	int listCount = 0;
	persist_read_list_count( &listCount );
	if ( listCount <= 0 )
	{
		LOG("Persist: List count not defined." );
		return -1;
	}
	int key = PERSIST_LIST_COUNT + listCount + 1;
	for ( int i = 0 ; i < listId ; ++i )
	{
		if ( persist_exists( key ) )
		{
			key += persist_read_int( key ) + 1;
		}
		else
		{
			LOG("Persist: Cannot found key for task count." );
			return -1;
		}
	}
	return key;
}

int persist_write_list_count( int count )
{
	persist_write_int( PERSIST_LIST_COUNT, count );
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
	return 0;
}

int persist_write_list( int listId, char* title )
{
	persist_write_string( PERSIST_LIST_COUNT+1+listId, title );
	return 0;
}

int persist_write_task( int listId, int taskId, char* title, int done )
{
	int key = persist_get_task_count_key( listId );
	if ( key <= 0 )
	{
		LOG("Persist: cannot found key for task count");
		return -1;
	}
	int sizeString = strlen( title ) + 2;
	char* string = malloc(sizeString);
	string[0] = done ? '1' : '0';
	strcat( string+1, title);
	persist_write_string( key+taskId+1, string );
	free( string );
	return 0;
}

int persist_read_list_count( int *count )
{
	if ( !persist_exists( PERSIST_LIST_COUNT ) )
	{
		LOG("Persist: reading not existing list");
		return -1;
	}
	*count = persist_read_int(PERSIST_LIST_COUNT);
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
	const int key = PERSIST_LIST_COUNT + 1 + listId;
	if ( !persist_exists( key ) )
	{
		LOG("Persist: reading not existing list");
		return -1;
	}
	persist_read_string( key, title, sizeTitle );
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
	const int sizeString = sizeTitle + 1;
	char *string = malloc( sizeString );
	persist_read_string( key, string, sizeString );
	*done = string[0] == '1';
	strncpy( title, string+1, sizeTitle );
	free( string );
	return 0;
}
