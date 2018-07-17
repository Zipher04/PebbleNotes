#include <pebble.h>
#include "comm.h"
#include "tasks.h"
#include "taskinfo.h"
#include "statusbar.h"
#include "options.h"
#include "misc.h"
#include "taskMenu.h"

static void init(void) {
	options_init();
	comm_init();
	ts_init();
	ti_init();
	sb_init();
	MenuInit();
	persist_write_int( 11, 0 );
	TrySyncWithPhone();
	// others...
}

static void deinit(void) {
	// others...
	MenuDeinit();
	sb_deinit();
	ti_deinit();
	ts_deinit();
	comm_deinit();
	options_deinit();
}

int main(void) {
  init();

  app_event_loop();
  deinit();
}
