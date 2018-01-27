#ifndef DAEMON
#define DAEMON

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <signal.h>
#include <syslog.h>

#define NOCHDIR NULL
#define CLOSEFD 0

int daemoninit(char *dir, int noclose);

#endif
