#ifndef _STATUSBAR_H
#define _STATUSBAR_H

#include <pebble.h>

void sb_init();
void sb_deinit();

// show the string in status bar
void sb_show(char*);

// delete and re-allocate buffer
char* sb_printf_alloc(int);

// get (already allocated) buffer
char* sb_printf_get();

// show current buffer in status bar
void sb_printf_update();

// hide layer and free memory
void sb_hide();

void sb_window_disappear_cb(Window*); // must be called in every window's onDisappear

#endif
