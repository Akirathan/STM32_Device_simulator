//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_CLIENT_HPP
#define DEVICE_SIMULATOR_CLIENT_HPP

#include <cstdint>
#include "http/request.hpp"
#include "http/response.hpp"
#include "device.hpp"
#include "interval_list.hpp"
#include "i_client_cb_recver.hpp"

namespace comm {

/**
 * Represents application specific client.
 *
 * Conforms to callback API.
*/
class Client {
private:
    static const size_t IP_ADDR_LEN = 16;
    static const size_t HOST_LEN = IP_ADDR_LEN + 7;

    enum await_state_t {
        AWAIT_NONE,
        AWAIT_CONNECT_RESPONSE,
        AWAIT_INTERVAL_TIMESTAMP_RESPONSE,
        AWAIT_INTERVALS,
        AWAIT_INTERVALS_ACK,
        AWAIT_TEMP_ACK
    };

public:
    static void init(const char *ip_addr, uint16_t port, IClientCbRecver *client_cb_recver);
    static void receiveCb(const http::Response &response);
    static bool sendConnectReq(const char *device_id);
    static bool setTemperature(const double temp, const uint32_t time_stamp);
    static bool setIntervals(const IntervalList &intervals, const uint32_t time_stamp);

private:
    static const constexpr char * CONNECT_URL = "/controllers/connect";

    static bool initialized;
    static char ipAddr[IP_ADDR_LEN];
    static uint16_t port;
    static char host[HOST_LEN];
    static await_state_t state;
    static char deviceId[Device::ID_LEN];
    static IClientCbRecver *clientCbRecver;

    static void initHost(const char *ip_addr, const uint16_t port);
    static void readConnectResponse(const http::Response &response);
    static http::Request createConnectReq(const char *device_id);
    static void callConnectedCb();
    static void callTempSentCb();
    static void callIntervalsSentCb();
    static void callIntervalsRecvCb(const IntervalList &interval_list);
};

} // namespace comm

#endif //DEVICE_SIMULATOR_CLIENT_HPP
