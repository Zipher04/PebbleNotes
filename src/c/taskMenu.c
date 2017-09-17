#include <pebble.h>
#include "taskinfo.h"
#include "tasks.h"
#include "misc.h"
#include "statusbar.h"
#include "taskMenu.h"

static const int SECTION_SIZE = 1;
static const int ITEM_SIZE = 3;

static Window *s_window;
static SimpleMenuLayer *s_menu_layer;
static SimpleMenuSection s_menu_section[MENU_SIZE];
static SimpleMenuItem s_menu_item[SECTION_SIZE];

/* Private functions */
static int g_currentTaskId;

void TaskDelete( int index, void *context )
{
	offline_set_task_status( taskId, -1 );
	ts_reload_items();
	window_stack_pop( true );
}

/* Public functions */
void menuShow( int taskId )
{
	g_currentTaskId = taskId;
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
    	.callback = NULL,
		};
	s_menu_item[itemId++] = (SimpleMenuItem) {
    	.title = "Delete task",
    	.subtitle = NULL,
    	.callback = TaskDelete,
		};
	s_menu_item[itemId++] = (SimpleMenuItem) {
    	.title = "Edit title",
    	.subtitle = NULL,
    	.callback = NULL,
		};
	s_menu_item[itemId++] = (SimpleMenuItem) {
    	.title = "Edit notes",
    	.subtitle = NULL,
    	.callback = NULL,
		};	
	assert( itemId == ITEM_SIZE, "Menu item count not match" );
	
	// init menu
	int sectionId = 0;
	s_menu_section[sectionId++] = (SimpleMenuSection) {
		.title = "Actions",
		.items = s_menu_item,
   		.num_items = 2,
		};
	assert( sectionId == SECTION_SIZE, "Menu section count not match" );
	
	s_menu_layer = simple_menu_layer_create( bounds, window, s_menu_section, 1, NULL );
  
	// Add the text layer to the window
	layer_add_child( window_layer, simple_menu_layer_get_layer(s_menu_layer));

}

void main_window_unload(Window *window) {
	simple_menu_layer_destroy(s_menu_layer);
}

void MenuInit()
{
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

void MenuDeinit(void) {

	// Destroy the window
	window_destroy(s_window);
}