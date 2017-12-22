#include "message.h"

message messageinit(char type, long size)
{
	message m;
	m.type = type;
	m.size = size;
	return m;
}

char *encode(message *m)
{
	static char buffer[numdigitsmssg];
	int num = snprintf(buffer, sizeof(buffer), messageformat, m->type, m->size);
	//fprintf(stderr, "encode: %d\n", num);
	if (num != numdigitschar + numdigitslong ) return NULL;
	return buffer;
}

message decode(char *s)
{
	message m;
	int num = sscanf(s, messageformat, &m.type, &m.size);
	//fprintf(stderr, "decode: %d\n", num);
	//if (num != numdigitschar + numdigitslong ) return nullmessage;
	return m;
}

int putmessage(int des, message *m)
{
	return write(des, encode(m), numdigitsmssg);
}

int getmessage(int des, message *m)
{
	char buffer[numdigitsmssg];
	int num = read(des, buffer, numdigitsmssg);
	*m = decode(buffer);
	return num;
}

int messagecmp(message s, message t)
{
	return abs(s.type - t.type) + abs(s.size - t.size);
}
