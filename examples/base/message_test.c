#include "message.h"
#include <fcntl.h>

#define FILE_PERMS ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
#define OPEN_FLAGS ( O_RDWR | O_CREAT )

enum messagetype { HELLO = 0, ECHO = 1 };

int main(){

char data[0xff] = "Hello, message module!!";

message m = messageinit(ECHO, sizeof(data));
message n = messageinit(HELLO, sizeof("hello"));

char messagestring[numdigitsmssg];
int num = snprintf(messagestring, sizeof(messagestring), "%s", encode(&m));
fprintf(stderr, "encoded message[%2lu]: %s\n", strlen(messagestring), messagestring);

message x = decode(messagestring);

fprintf(stderr, "type: [%03d][%d]\n", x.type, x.type);
fprintf(stderr, "size: [%020ld][%ld]\n", x.size, x.size);

int fd1 = open("message.cache", OPEN_FLAGS, FILE_PERMS);
putmessage(fd1, &m);
close(fd1);

message z;
int fd2 = open("message.cache", OPEN_FLAGS, FILE_PERMS);
getmessage(fd2, &z);
close(fd2);

fprintf(stderr, "message m: %s\n", encode(&m));
fprintf(stderr, "message z: %s\n", encode(&z));
fprintf(stderr, "message n: %s\n", encode(&n));

fprintf(stderr, "|m - z| = %d\n", messagecmp(m, z));
fprintf(stderr, "|m - n| = %d\n", messagecmp(m, n));
fprintf(stderr, "|z - n| = %d\n", messagecmp(z, n));

return 0; }

