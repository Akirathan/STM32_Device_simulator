//
// Created by mayfa on 21.6.18.
//

#include "client_timer.hpp"
#include "client.hpp"
#include "rt_assert.h"
#include <signal.h>
#include <time.h>

namespace comm {

bool ClientTimer::initialized = false;

void ClientTimer::init()
{
    struct sigaction action;
    action.sa_handler = ClientTimer::timeoutHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGUSR1, &action, nullptr) != 0) {
        perror("sigaction");
    }

    initialized = true;
}

void ClientTimer::start(int seconds)
{
    rt_assert(initialized, "ClientTimer must be initialized");

    struct sigevent sevp;
    sevp.sigev_notify = SIGEV_SIGNAL;
    sevp.sigev_signo = SIGUSR1;
    sevp.sigev_value.sival_ptr = nullptr;

    timer_t timer_id;
    timer_create(CLOCK_REALTIME, &sevp, &timer_id);

    struct timespec time;
    time.tv_nsec = 0;
    time.tv_sec = seconds;

    struct timespec null_time {0, 0};

    struct itimerspec timer_spec {
            .it_interval = null_time,
            .it_value = time
    };

    if (timer_settime(timer_id, 0, &timer_spec, nullptr) != 0) {
        perror("timer_settime");
    }
}

void ClientTimer::timeoutHandler(int sigNum)
{
    Client::startCycle();
}

} // namespace comm