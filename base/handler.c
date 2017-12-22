#include "handler.h"

// todo: encapsulate the shared library linking facilities in this module
// note: handlers in this file are 'simple' TCP I/O handlers (maybe moved in future)

long getdata(int fd, char *store, int size)
{
	if (store == NULL) return -1;

	ssize_t all = 0;
	ssize_t num = 0;

	while (all < size) {
		while (((num = recv(fd, store + all, size - all, 0)) == -1) && (errno == EINTR));
		all += num;
	}

	return all;
}

long putdata(int fd, char *store, int size)
{
	if (store == NULL) return -1;

	ssize_t all = 0;
	ssize_t num = 0;

	while (all < size) {
		while (((num = send(fd, store + all, size - all, 0)) == -1) && (errno == EINTR));
		all += num;
	}

	return all;
}

long hellohandle(int fd, char *store, int size)
{
	return snprintf(store, size, "Hello, Handler! [%d]", fd);
}
