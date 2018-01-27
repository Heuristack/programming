#include "timing.h"

static long million = 1000000L;

char *timestamp()
{
	static char timestampstring[0x5f];
	time_t t;
	time(&t);
	strftime(timestampstring, 0x5f, "%Y%m%d%H%M%S", localtime(&t));
	return timestampstring;
}

instant timeinstant(timepoint t)
{
	return t.tv_sec + t.tv_usec/1000000.0;
}

timepoint timepin(timepoint *p)
{
	gettimeofday(p, NULL);
	return *p;
}

timerange timeint(timepoint s, timepoint e)
{
	return ( e.tv_sec - s.tv_sec ) + ( e.tv_usec - s.tv_usec)/1000000.0;
}

int microsleep(long microseconds)
{
	struct timespec ts;
	ts.tv_sec = microseconds / million;
	ts.tv_nsec = (microseconds % million) * 1000;
	return nanosleep(&ts, NULL);
}

