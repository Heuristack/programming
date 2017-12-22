#ifndef LOGGER
#define LOGGER

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>

#define logtrace(...) logprintf( __FILE__, __FUNCTION__, __LINE__, TRACE, __VA_ARGS__ )
#define logerror(...) logprintf( __FILE__, __FUNCTION__, __LINE__, ERROR, __VA_ARGS__ )
#define logstats(...) logprintf( __FILE__, __FUNCTION__, __LINE__, STATS, __VA_ARGS__ )

#define LOG(...) logprintf( NULL, NULL, -1, TRACE, __VA_ARGS__ )

#define TRACE 0
#define STATS 1
#define ERROR 2

int getseveritylevel(char *severity);

int logopen(char *filename, int severity);
int logdup(int filedes, int severity);
int logclose(void);

int logprintf(char *file, char *function, int line, int severity, char *format, ...);

#endif
