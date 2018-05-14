//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_CLIENT_HPP
#define DEVICE_SIMULATOR_CLIENT_HPP

#include <cstdint>

namespace comm {

/**
* Represents application specific client.
*
* @note communication may always result in error that'swhy all function members that use
*       TCP/IP returns bool (or other representation of error).
*/
class Client {
public:
    static void init(const char *ip_addr, uint16_t port);
    static bool connect(Device &device, uint32_t *server_real_time);
    static bool sendTemperature(const double temp, const uint32_t time_stamp);
    static bool sendIntervals(const IntervalList &intervals, const uint32_t time_stamp);
    static bool receiveIntervals(IntervalList *intervals);
    static bool requestIntervalTimeStamp(uint32_t *time_stamp);

private:
    static bool initialized;
    static char ipAddr[9];
    static uint16_t port;
};

} // namespace comm

#endif //DEVICE_SIMULATOR_CLIENT_HPP
