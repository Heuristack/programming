#include "logger.h"

#define FILE_PERMS ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
#define OPEN_FLAGS ( O_WRONLY | O_APPEND | O_CREAT )

static int logfd = -1;
static int level = TRACE;
static int result = 0;

int getseveritylevel(char *severity)
{
	static severitylevel = TRACE;
	if (!strcmp(severity, "TRACE") || !strcmp(severity, "trace")) severitylevel = TRACE;
	if (!strcmp(severity, "STATS") || !strcmp(severity, "stats")) severitylevel = STATS;
	if (!strcmp(severity, "ERROR") || !strcmp(severity, "error")) severitylevel = ERROR;
	return severitylevel;
}

static char *getseverity(int severity)
{
	static char *pseverity = "TRACE";
	if (severity == TRACE) pseverity = "TRACE";
	if (severity == ERROR) pseverity = "ERROR";
	if (severity == STATS) pseverity = "STATS";
	return pseverity;
}

static char *getlogtime()
{
	static char loggingtime[0x5f];
	time_t t;
	time(&t);
	strftime(loggingtime, 0x5f, "%Y%m%d%H%M%S", localtime(&t));
	return loggingtime;
}

static ssize_t dogwrite(int filedes, void *buffer, size_t size) {
	ssize_t num;
	while (((num = write(filedes, buffer, size)) == -1) && (errno == EINTR));
	return num;
}

int logopen(char *filename, int severity)
{
	logfd = open(filename, OPEN_FLAGS, FILE_PERMS);
	level = severity;
	return logfd;
}

int logdup(int filedes, int severity)
{
	logfd = dup(filedes);
	level = severity;
	return logfd;
}

int logclose()
{
	result = close(logfd);
	return result;
}

int logprintf(char *file, char *function, int line, int severity, char *format, ...)
{
	if (severity < level) return 0;
	static char header[0x100];
	if (file != NULL && function != NULL && line != -1)
		snprintf(header, sizeof(header), "%s %10s(%10s):%04d ", getlogtime(), file, function, line);
	else
		snprintf(header, sizeof(header), "%s ", getlogtime());

	static char message[0x400];
	va_list arglist;
	va_start(arglist, format);
		vsnprintf(message, sizeof(message), format, arglist);

	static char buffer[0x500];
	ssize_t num = snprintf(buffer, sizeof(buffer), "%s[%s] %s\n", header, getseverity(severity), message);
	if (num < 0) return -1;
	return (int) dogwrite(logfd, buffer, (size_t)num);
}

