
#ifndef _PERSIST_H
#define _PERSIST_H

const int persist_write_list_count( int count );
const int persist_write_task_count( int listId, int count );

const int persist_write_list( int listId, char* title );
const int persist_write_task( int listId, int taskId, char* title, bool done );

const int persist_write_list( int listId, char* title );
const int persist_write_task( int listId, int taskId, char* title, bool done );

const int persist_read_list_count( int *count );
const int persist_read_task_count( int listId, int *count );

const int persist_read_list( int listId, char* title, int sizeTitle );
const int persist_read_task( int listId, int taskId, char* title, int sizeTitle, bool *done );

#endif