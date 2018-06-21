//
// Created by mayfa on 21.6.18.
//

#ifndef DEVICE_SIMULATOR_CLIENT_TIMER_HPP
#define DEVICE_SIMULATOR_CLIENT_TIMER_HPP

namespace comm {

class ClientTimer {
public:
    static void init();
    static void start(int seconds);
private:
    static void timeoutHandler(int sigNum);

    static bool initialized;
};

} // namespace comm

#endif //DEVICE_SIMULATOR_CLIENT_TIMER_HPP
