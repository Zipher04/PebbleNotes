#include <pebble.h>

#include "misc.h"

#include "isoTime.h"

void GetIsoTime( char *buffer, int size )
{
	time_t rawTime;
	time(&rawTime);
	struct tm * timeinfo = gmtime(&rawTime);
	int success = strftime( buffer, size, "%FT%T.000Z", timeinfo );
	assert( success != 0, "time buffer too small" );
	//2017-09-06T09:07:30.000Z
	
}