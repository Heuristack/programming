#include <sys/poll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

using namespace std;

int main (void)
{
    struct pollfd fds[2];

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;

    if (int n = poll(fds, 2, 5); n > 0) {
        if (fds[0].revents & POLLIN ) {
            cout << "0 is ready" << endl;
        }
        if (fds[1].revents & POLLOUT) {
            cout << "1 is ready" << endl;
        }
    }
    else if (n == 0) {
        cout << "timeout ..." << endl;
    }
    else {
        cout << strerror(errno) << endl;
    }

    return 0;
}

