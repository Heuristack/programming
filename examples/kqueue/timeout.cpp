#include <sys/event.h>
#include <sys/types.h>
#include <sys/time.h>
#include <iostream>

int main()
{
    struct kevent change;
    struct kevent event;
    EV_SET(&change, 1, EVFILT_TIMER, EV_ADD | EV_ENABLE, NOTE_NSECONDS, 5'000'000'000, 0);
    int kq = kqueue();
    int ne = kevent(kq, &change, 1, &event, 1, NULL);
    if ((ne > 0) && !(event.flags & EV_ERROR)) {
        std::cout << "kqueue: timeout!" << std::endl;
    }
}

