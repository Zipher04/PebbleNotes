#ifndef _TASKS_H
#define _TASKS_H

typedef struct {
	int id;
	bool done;
	char* title;
	char* notes;
} TS_Item;

/**
 * Create tasks window.
 */
void ts_init();
void ts_deinit();

/**
 * Create tasks view for specific listId.
 */
void ts_show_pebble( void );
//void ts_show(int listId, char* listTitle);
bool ts_is_active();
//int ts_current_listId();

/**
 * Check tasks window is ready to show.
 * @return listId for the tasks to show. -1 if tasks not ready.
 */
//int ts_current_if_complete();
void ts_set_count(int);
void ts_set_item(int, TS_Item);
//void ts_append_item(TS_Item);
void ts_update_item_state_by_id(int, bool);

void ts_reload_items(void);
void ts_show_detail( int taskIndex );
#endif
