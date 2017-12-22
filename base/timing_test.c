#include "timing.h"
#include <unistd.h>

int main(){
	printf("%s: enter!\n", timestamp());

	timepoint start;
	timepin(&start);

	sleep(3);

	timepoint currt;
	timepin(&currt);

	timerange interval = timeint(start, currt);

	printf("since: %.4f time elapse: %.4f seconds!\n", timeinstant(start), timeint(start, currt));
	printf("time elapse: %.4f seconds until %.4f!\n", interval, timeinstant(currt));

	printf("%s: leave!\n", timestamp());

return 0; }
