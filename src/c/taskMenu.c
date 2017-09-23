#include <pebble.h>
#include "taskinfo.h"
#include "tasks.h"
#include "misc.h"
#include "statusbar.h"
#include "offline.h"
#include "isoTime.h"
#include "taskMenu.h"
#include "consts.h"
#include "tertiary_text.h"

#define SECTION_SIZE 1
#define ITEM_SIZE 4
#define CELL_HEIGHT 40

static Window *s_window;
static SimpleMenuLayer *s_menu_layer;
static SimpleMenuSection s_menu_section[SECTION_SIZE];
static SimpleMenuItem s_menu_item[ITEM_SIZE];

/* Private functions */
static int g_currentTaskIndex;

void TaskShowNotes( int index, void *context )
{
	ts_show_detail( g_currentTaskIndex );
}

void TaskDelete( int index, void *context )
{
	char id[SIZE_TASK_ID] = "";
	PersistGetTaskId( g_currentTaskIndex, id, SIZE_TASK_ID );
	if ( 0 == strlen( id ) )
	{
		PersistRemoveTask( g_currentTaskIndex );
	}
	else
	{
		PersistSetTaskStatus( g_currentTaskIndex, -1 );
		PersistUpdateTaskUpdateTime( g_currentTaskIndex );
	}
	
	ts_reload_items();
	window_stack_pop( true );
}

void TertiaryTaskEditTitleCallBack( const char* result, size_t result_length, void* extra )
{
	if ( 0 == result_length )
		return;
	PersistSetTaskTitle( g_currentTaskIndex, (char*)result );
	PersistUpdateTaskUpdateTime( g_currentTaskIndex );
	ts_reload_items();
	window_stack_pop( true );
}

void TaskEditTitle( int index, void *context )
{
	LOG("TaskEditTitle Calling tertiary");
	tertiary_text_prompt( "Edit task title", TertiaryTaskEditTitleCallBack, 0 );
}

void TertiaryTaskEditNotesCallBack( const char* result, size_t result_length, void* extra )
{
	PersistSetTaskNotes( g_currentTaskIndex, (char*)result );
	PersistUpdateTaskUpdateTime( g_currentTaskIndex );
	ts_reload_items();
	window_stack_pop( true );
}

void TaskEditNotes( int index, void *context )
{
	LOG("TaskEditNotes Calling tertiary");
	tertiary_text_prompt( "Edit task notes", TertiaryTaskEditNotesCallBack, 0 );
}

static int16_t get_cell_height_cb( struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context )
{
	return CELL_HEIGHT;
}

/* Public functions */
void menuShow( int taskIndex )
{
	g_currentTaskIndex = taskIndex;
	window_stack_push( s_window, true );
}

void main_window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	
	//init sections
	int itemId = 0;
	s_menu_item[itemId++] = (SimpleMenuItem) {
		.title = "View detail",
		.subtitle = NULL,
		.callback = TaskShowNotes,
	};
	s_menu_item[itemId++] = (SimpleMenuItem) {
		.title = "Delete task",
		.subtitle = NULL,
		.callback = TaskDelete,
	};
	s_menu_item[itemId++] = (SimpleMenuItem) {
		.title = "Edit title",
		.subtitle = NULL,
		.callback = TaskEditTitle,
	};
	s_menu_item[itemId++] = (SimpleMenuItem) {
		.title = "Edit notes",
		.subtitle = NULL,
		.callback = TaskEditNotes,
	};	
	assert( itemId == ITEM_SIZE, "Menu item count not match" );
	
	// init menu
	int sectionId = 0;
	s_menu_section[sectionId++] = (SimpleMenuSection) {
		.title = "Actions",
		.items = s_menu_item,
		.num_items = ITEM_SIZE,
	};
	assert( sectionId == SECTION_SIZE, "Menu section count not match" );
	
	s_menu_layer = simple_menu_layer_create( bounds, window, s_menu_section, 1, NULL );
	
	// Add the text layer to the window
	layer_add_child( window_layer, simple_menu_layer_get_layer(s_menu_layer));

}

void main_window_unload(Window *window) {
	simple_menu_layer_destroy(s_menu_layer);
}

void MenuInit( void ) {
	// Create a window and get information about the window
	s_window = window_create();
	window_set_window_handlers(s_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	});
	// Push the window, setting the window animation to 'true'
	// window_stack_push(s_window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Menu inited");
}

void MenuDeinit( void ) {

	// Destroy the window
	window_destroy(s_window);
}