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
    static void setTemperature(const double temp, const uint32_t time_stamp);
    static void setIntervals(const IntervalList &intervals);

private:
    static const constexpr char * CONNECT_URL = "/controllers/connect";
    static const constexpr char * TEMP_URL = "/controllers/actual/temp";
    static const constexpr char * INTERVALS_URL = "/controllers/config/intervals";
    static const constexpr char * INTERVALS_TIMESTAMP_URL = "/controllers/config/intervals/timestamp";

    static bool initialized;
    static char ipAddr[IP_ADDR_LEN];
    static uint16_t port;
    static char host[HOST_LEN];
    static await_state_t state;
    static char deviceId[Device::ID_LEN];
    /// Preset temperature by device that will be posted to server when appropriate.
    static double temperature;
    static uint32_t temperatureTimestamp;
    /// Interval list set by device that will be posted to server when appropriate.
    static IntervalList intervalList;
    /// Temporary storage for intervals timestamp from server that is read in
    /// readIntervalTimestampResp. Note that this member is necessary because
    /// server does not send timestamp with intervals in one response.
    static uint32_t tempIntervalsTimestamp;
    static IClientCbRecver *clientCbRecver;

    static void initHost(const char *ip_addr, const uint16_t port);
    static bool send(const http::Request &request, bool await_body);
    static void readConnectResponse(const http::Response &response);
    static void readIntervalTimestampResp(const http::Response &response);
    static void readIntervalsResp(const http::Response &response, const uint32_t time_stamp);
    static void readIntervalsAckResp(const http::Response &response);
    static void readTempAckResp(const http::Response &response);
    static http::Request createConnectReq(const char *device_id);
    static http::Request createIntervalTimestampReq();
    static http::Request createGetIntervalsReq();
    static http::Request createPostIntervalsReq(const IntervalList &interval_list);
    static http::Request createPostTemperature(const double temp, const uint32_t time_stamp);
    static http::Request createGetReq(const char *url);
    static http::Request createPostReq(const char *url, const char *body, const char *content_type);
    static void callConnectedCb();
    static void callTempSentCb();
    static void callIntervalsSentCb();
    static void callIntervalsRecvCb(const IntervalList &interval_list);
};

} // namespace comm

#endif //DEVICE_SIMULATOR_CLIENT_HPP
