#include "daemon.h"

int daemoninit(char *dir, int noclose)
{

	int result = 0;

	umask(0);

	struct rlimit resourcelimit;
	result = getrlimit(RLIMIT_NOFILE, &resourcelimit);
	if (result < 0) { perror("daemonize: getrlimit failed!"); exit(1); }

	pid_t pid;
	if ((pid = fork()) < 0) { perror("daemonize: fork failed!"); exit(1); }
	if (pid != 0) exit(0); else setsid();

	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	result = sigaction(SIGHUP, &sa, NULL);
	if (result < 0) { perror("daemonize: sigaction failed!"); exit(1); }

	if ((pid = fork()) < 0) { perror("daemonize: fork failed!"); exit(1); }
	if (pid != 0) exit(0);

	if (dir) result = chdir(dir); else result = 0;
	if (result < 0) { perror("daemonize: chdir failed!"); exit(1); }

	if (noclose) return 0;
	rlim_t maxnumfiles = resourcelimit.rlim_max;
	if (maxnumfiles == RLIM_INFINITY) maxnumfiles = 0x400;
	for (int fd = 0; fd < maxnumfiles; fd++) close(fd);

	open("/dev/null", O_RDWR); dup(0); dup(0);

	return 0;
}
