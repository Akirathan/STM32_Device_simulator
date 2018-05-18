//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_CLIENT_HPP
#define DEVICE_SIMULATOR_CLIENT_HPP

#include <cstdint>
#include "http/response.hpp"
#include "device.hpp"
#include "interval_list.hpp"

namespace comm {

/**
* Represents application specific client.
 *
 * Conforms to callback API.
*/
class Client {
    enum await_state_t {
        AWAIT_CONNECT_RESPONSE,
        AWAIT_INTERVAL_TIMESTAMP_RESPONSE,
        AWAIT_INTERVALS,
        AWAIT_INTERVALS_ACK,
        AWAIT_TEMP_ACK
    };

public:
    static void init(const char *ip_addr, uint16_t port);
    /**
     * This method is specific for BSD socket API.
     */
    static void poll();
    static void receiveCb(const uint8_t *buff, const size_t buff_size);
    static bool sendConnectReq(Device *device, uint32_t *server_real_time);
    static bool sendTemperature(const double temp, const uint32_t time_stamp);
    static bool sendIntervals(const IntervalList &intervals, const uint32_t time_stamp);
    static bool receiveIntervals(IntervalList *intervals);
    static bool requestIntervalTimeStamp(uint32_t *time_stamp);

private:
    static bool initialized;
    static char ipAddr[9];
    static uint16_t port;
    static await_state_t state;
    static Device *currDevice;

    static bool readResponse(const uint8_t *buff, const size_t buff_size, http::Response *response);
};

} // namespace comm

#endif //DEVICE_SIMULATOR_CLIENT_HPP
