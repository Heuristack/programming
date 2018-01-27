#include "handler.h"

int main(){

char store[0xff];
handler hello = hellohandle;
hello(99, store, sizeof(store));
fprintf(stderr, "%s\n", store);

return 0; }
