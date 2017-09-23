#ifndef _COMMON_H
#define _COMMON_H

#ifndef NDEBUG
#define LOG(args...) APP_LOG(APP_LOG_LEVEL_DEBUG, args)
#else
#define LOG(args...) 
#endif
#define assert(e, msg...) if(!(e)) { APP_LOG(APP_LOG_LEVEL_ERROR, msg); return; }
#define assert_oom(e, msg...) if(!(e)) { APP_LOG(APP_LOG_LEVEL_ERROR, msg); sb_show("OOM"); }

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif
