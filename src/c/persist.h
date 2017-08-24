
#ifndef _PERSIST_H
#define _PERSIST_H

int persist_write_list_count( int count );
int persist_write_task_count( int listId, int count );

int persist_write_list( int listId, char* title );
int persist_write_task( int listId, int taskId, char* title, int done );

int persist_read_list_count( int *count );
int persist_read_task_count( int listId, int *count );

int persist_read_list( int listId, char* title, int sizeTitle );
int persist_read_task( int listId, int taskId, char* title, int sizeTitle, int *done );

#endif