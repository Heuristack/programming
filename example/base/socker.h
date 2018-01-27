#ifndef SOCKER
#define SOCKER

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int socker(char *host, short port, struct sockaddr_in *address);
int binder(int sock, char *host, short port);

char *gethost(struct sockaddr *address);
short getport(struct sockaddr *address);

char *getsockhost(int sock);
short getsockport(int sock);

int setsockreuse(int sock);

#endif
