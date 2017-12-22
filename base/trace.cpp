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
#include <execinfo.h>

#define FILE_PERMS ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
#define OPEN_FLAGS ( O_WRONLY | O_APPEND | O_CREAT )

int magic_trace(char *filename, char *file, char *function, int line, char *format, ...)
{
	static char loggingtime[0x5f];
	time_t t;
	time(&t);
	strftime(loggingtime, 0x5f, "%Y%m%d%H%M%S", localtime(&t));

	static char header[0x100];
	if (file != NULL && function != NULL && line != -1)
		snprintf(header, sizeof(header), "[%s %30s(%30s):%04d]", loggingtime, file, function, line);
	else
		snprintf(header, sizeof(header), "[%s]", loggingtime);

	static char message[0x10000];
	va_list arglist;
	va_start(arglist, format);

	vsnprintf(message, sizeof(message), format, arglist);

	static char buffer[0x10000];
	ssize_t num = snprintf(buffer, sizeof(buffer), "%s : %s\n", header, message);
	if (num < 0) return -1;

	int fd = open(filename, OPEN_FLAGS, FILE_PERMS);
    ssize_t n = 0;
    while ((n = write(fd, buffer+n, (size_t)(num-n))) < (num-n));
	close(fd);
	return (int)num;
}

int stack_trace(char *filename)
{
	int fd = open(filename, OPEN_FLAGS, FILE_PERMS);

	void *frames[0xff];

	size_t size = backtrace (frames, 0xff);
	backtrace_symbols_fd(frames, size, fd);

	return close(fd);
}

int force_trace(char *filename, const char *p, int num)
{
	int fd = open(filename, OPEN_FLAGS, FILE_PERMS);
    ssize_t n = 0;
    while ((n = write(fd, p+n, (size_t)(num-n))) < (num-n));
    write(fd,"\n",1);
	close(fd);
    return num;
}

