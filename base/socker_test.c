#include "socker.h"
#include <stdio.h>
#include <unistd.h>

int main(){

	struct sockaddr_in address;
	int sd = socker("127.0.0.1", 8848, &address);
	if (sd < 0) { perror("socker failed!"); return -1; }
	fprintf(stderr, "%s\n", "socker successed!");

	fprintf(stderr, "connect to --> ipaddress: %s portnum: %d\n", gethost((struct sockaddr *)&address), getport((struct sockaddr *)&address));
	int result = connect(sd, (struct sockaddr *)(&address), (socklen_t)(sizeof(address)));
	if (result < 0 ) { perror("connect failed!"); return  -1; }
	fprintf(stderr, "%s\n", "connect successed!");

	close(sd);

return 0; }
