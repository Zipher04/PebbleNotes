
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


#endif