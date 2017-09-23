
#ifndef _OFFLINE_H
#define _OFFLINE_H

/**
 * Read lists from persist data
 */
int offline_read_lists( void );

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
void PersisitSetListId( char* id );
void PersisitGetListId( char* id, int length );

/**
 * Number of tasks inside list
 */
void PersistSetListLength( int length );
int PersistGetListLength( void );

/**
 * Read last sync time. Will be "" if never synced.
 */
void PersistSetListSyncTime( char* time );
void PersistGetListSyncTime( char* time, int length );

/**
 * id will be "" for task never synced.
 *@param length is at least 46.
 */
void PersistSetTaskId( int i, char* id );
void PersistGetTaskId( int i, char* id, int length );

/**
 *
 */
void PersistSetTaskTitle( int i, char* title );
void PersistGetTaskTitle( int i, char* title, int length );

/**
 *
 */
void PersistSetTaskNotes( int i, char* note );
void PersistGetTaskNotes( int i, char* note, int length );

/**
 * @para status: 0:unchecked, 1:checked, -1: deleted
 */
void PersistSetTaskStatus( int i, int status );
int PersistGetTaskStatus( int i );

/**
 * The time the task is last modified. Will be "" if never synced
 *@param length is at least 26.
 */
void PersistSetTaskUpdateTime( int i, char* time );
void PersistUpdateTaskUpdateTime( int i );
void PersistGetTaskUpdateTime( int i, char* time, int length );

void PersistRemoveTask( int i );

#endif