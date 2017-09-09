
#include <time.h>

#include "misc.h"
#include "isoTime.h"

void GetIsoTime( char *buffer, int size )
{
	assert( size >= 25, "Error isoTime: buffer too small");
	
	time_t rawTime;
	struct tm *timeInfo;
	
	time( &rawTime );
	timeInfo = gmtime( &rawTime );
	
	int success = strftime ( buffer, size, "%FT%T.000Z", timeInfo );
	//2017-09-07T14:41:59.000Z
	
	assert( success, "Error isoTime: buffer too small");
}