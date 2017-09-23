#ifndef _COMMON_H
#define _COMMON_H

#ifndef NDEBUG
#define LOG(...) APP_LOG(APP_LOG_LEVEL_DEBUG, __VA_ARGS__)
#else
#define LOG(...) 
#endif
#define assert(e, ...) if(!(e)) { APP_LOG(APP_LOG_LEVEL_ERROR, __VA_ARGS__); return; }
#define assert_oom(e, ...) if(!(e)) { APP_LOG(APP_LOG_LEVEL_ERROR, __VA_ARGS__); sb_show("OOM"); }

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif
