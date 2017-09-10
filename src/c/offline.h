
#ifndef _OFFLINE_H
#define _OFFLINE_H

/**
 * Read lists from persist data
 */
int offline_read_lists(void );

/**
 * Read tasks from persist data
 */
int offline_read_tasks( int listId );


//==========================================================
// New API for listing "pebble"
//==========================================================

/**
 * Read tasks from list named "pebble" from persist
 */
void offline_read_list_pebble( void );

/**
 *
 *@param length is at least 34.
 */
void offline_set_list_id( char* id );
void offline_get_list_id( char* id, int length );

/**
 * Number of tasks inside list
 */
void offline_set_list_length( int length );
int offline_get_list_length( void );

/**
 * Read last sync time. Will be "" if never synced.
 */
void offline_set_list_sync_time( char* time );
void offline_get_list_sync_time( char* time, int length );
 
/**
 * id will be "" for task never synced.
 *@param length is at least 46.
 */
void offline_set_task_id( int i, char* id );
void offline_get_task_id( int i, char* id, int length );
 
/**
 * 
 */
void offline_set_task_title( int i, char* title );
void offline_get_task_title( int i, char* title, int length );
 
/**
 * 
 */
void offline_set_task_note( int i, char* note );
void offline_get_task_note( int i, char* note, int length );
 
/**
 * @para status: 0:unchecked, 1:checked, -1: deleted
 */
void offline_set_task_status( int i, int status );
int offline_get_task_status( int i );

/**
 * The time the task is last modified. Will be "" if never synced
 *@param length is at least 26.
 */
void offline_set_task_update_time( int i, char* time );
void offline_get_task_update_time( int i, char* time, int length );

#endif