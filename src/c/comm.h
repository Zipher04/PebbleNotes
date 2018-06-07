/*
 * This module handles most of the watch-phone communication.
 */

#ifndef _COMM_H
#define _COMM_H

//void comm_query_list( void );

// read lists
//void comm_query_tasklists();

// read tasks from a list
//void comm_query_tasks(int listId);

// Not implemnted
//void comm_query_task_details(int, int);

// Done/undone an existing task
//void comm_update_task_status(int listId, int taskId, bool newStatus);

// Create a new task
//void comm_create_task(int listId, char* title, char* notes);

typedef void(* CommJsReadyCallback)(void *data);

// Do something when JS is ready, not used
//void comm_on_js_ready(CommJsReadyCallback*, void*);

// Returns false if there is no bluetooth connection
// or there is unsent message waiting (usually if JS was not loaded yet)
// If not available, show message in statusbar
bool comm_is_available();

bool comm_is_available_silent(); // don't update statusbar

/**
 * Register app message handler
 */
void comm_init();
void comm_deinit();

void TrySyncWithPhone( void );
void SentListToPhone( void );

#endif
