#ifndef MESSAGE
#define MESSAGE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define numdigitschar 3
#define numdigitslong 20
#define numdigitsmssg 24

#define messageformat "%03d%020ld"


typedef struct message {
	char  type;
	long  size;
} message;

static message nullmessage = {0,0};

message messageinit(char type, long size);

char *encode(message *m);
message decode(char *ms);

int putmessage(int des, message *m);
int getmessage(int des, message *m);

int messagecmp(message s, message t);

#endif

