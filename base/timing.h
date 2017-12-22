#ifndef TIMING
#define TIMING

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

char *timestamp(void);

typedef struct timeval timepoint;
typedef double timerange;
typedef double instant;

instant timeinstant(timepoint t);

timepoint timepin(timepoint *p);
timerange timeint(timepoint s, timepoint e);


int microsleep(long microseconds);

#endif
