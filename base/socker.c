#include "socker.h"

//todo: add UDP/multicast/broadcast support
//todo: investigate raw socket support feasibility
//todo: make socker stable

int socker(char *host, short port, struct sockaddr_in *address)
{
	address->sin_family = AF_INET;
	address->sin_addr.s_addr = inet_addr(host);
	address->sin_port = htons(port);

	return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int setsockreuse(int sock)
{
	int option = 1;
	return setsockopt(sock, IPPROTO_TCP, SO_REUSEADDR/* | SO_REUSEPORT (Linux does NOT support!) */, &option, sizeof(option));
}

int binder(int sock, char *host, short port)
{
	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(host);
	address.sin_port = htons(port);

	return bind(sock, (struct sockaddr *)&address, (socklen_t)(sizeof(address)));
}

char *gethost(struct sockaddr *address)
{
	struct sockaddr_in *ipv4address = (struct sockaddr_in *)address;
	return inet_ntoa(ipv4address->sin_addr);
}

short getport(struct sockaddr *address)
{
	struct sockaddr_in *ipv4address = (struct sockaddr_in *)address;
	return ntohs(ipv4address->sin_port);
}

char *getsockhost(int sock)
{
	struct sockaddr address;
	socklen_t address_len = sizeof(struct sockaddr);
	int r = getsockname(sock, &address, &address_len);
	if (r < 0) return NULL;
	return gethost(&address);
}

short getsockport(int sock)
{
	struct sockaddr address;
	socklen_t address_len = sizeof(struct sockaddr);
	int r = getsockname(sock, &address, &address_len);
	if (r < 0) return NULL;
	return getport(&address);
}
