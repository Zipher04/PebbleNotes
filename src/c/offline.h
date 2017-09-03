
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
 * Set list is modified. Will be checked before sync.
 */
void offline_set_list_modified( int modified );
int offline_is_list_modified( void );

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
 * @para done: 0:unchecked, 1:checked
 */
void offline_set_task_done( int i, int done );
int offline_is_task_done( int i );

/**
 * The time the task is last modified. Will be "" if never synced
 *@param length is at least 26.
 */
void offline_set_task_update_time( int i, char* time );
void offline_get_task_update_time( int i, char* time, int length );

#endif