#ifndef HANDLER
#define HANDLER

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define maxnumhandler 0xff

typedef int (*handler)(int, char*, int);
typedef int (*handlertable[maxnumhandler])(int, char*, int);

//I/O  handlers
long getdata(int fd, char *store, int size);
long putdata(int fd, char *store, int size);

long hellohandle(int, char*, int);

#endif
