#pragma once

#include "tasks.h"

void ti_init();
void ti_deinit();
void ti_show(int, TS_Item);
bool ti_is_active();
int ti_current_taskId();

#endif
