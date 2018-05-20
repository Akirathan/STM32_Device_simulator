//
// Created by mayfa on 14.5.18.
//

#include "client.hpp"
#include "http/response_buffer.hpp"
#include "tcp_driver.hpp"

namespace comm {

bool                  Client::initialized = false;
char                  Client::ipAddr[IP_ADDR_LEN];
uint16_t              Client::port = 0;
char                  Client::host[HOST_LEN];
Client::await_state_t Client::state = AWAIT_NONE;
char                  Client::deviceId[Device::ID_LEN];
IClientCbRecver *     Client::clientCbRecver = nullptr;

/**
 *
 * @param ip_addr
 * @param port
 * @param client_cb_recver ... receiver of all client callbacks, may be NULL.
 */
void Client::init(const char *ip_addr, uint16_t port, IClientCbRecver *client_cb_recver)
{
    if (!initialized) {
        std::strcpy(ipAddr, ip_addr);
        Client::port = port;
        initHost(ip_addr, port);
        clientCbRecver = client_cb_recver;
        initialized = true;
    }
}

void Client::receiveCb(const http::Response &response)
{
    switch (state) {
        case AWAIT_CONNECT_RESPONSE:
            readConnectResponse(response);
            break;
        case AWAIT_INTERVAL_TIMESTAMP_RESPONSE:break;
        case AWAIT_INTERVALS:break;
        case AWAIT_INTERVALS_ACK:break;
        case AWAIT_TEMP_ACK:break;
        case AWAIT_NONE:break;
    }
}

/**
 * Sends connection request to the server.
 *
 * @param device_id ... device id (TODO: encrypted?)
 * @return false when TCPDriver fails to send data.
 */
bool Client::sendConnectReq(const char *device_id)
{
    std::strcpy(deviceId, device_id);
    state = AWAIT_CONNECT_RESPONSE;

    TcpDriver::connect(ipAddr, port);

    http::Request req = createConnectReq(device_id);
    char buffer[http::Request::TOTAL_SIZE];
    req.toBuffer(buffer);

    http::ResponseBuffer::awaitBody();
    return TcpDriver::send(reinterpret_cast<uint8_t *>(buffer), req.getSize());
}

void Client::initHost(const char *ip_addr, const uint16_t port)
{
    char port_str[7];
    std::sprintf(port_str, "%u", port);

    char *host_ptr = host;
    std::strcpy(host_ptr, ip_addr);
    host_ptr += std::strlen(ip_addr);
    *(host_ptr++) = ':';
    std::strcpy(host_ptr, port_str);
}

/**
 * Response from server should contain server_real_time in body.
 * @param buff      ... received buffer from server.
 * @param response ... received buffer size.
 */
void Client::readConnectResponse(const http::Response &response)
{
    if (response.getStatusCode() != http::Response::OK) {
        // TODO: error handling
        sendConnectReq(deviceId);
        return;
    }

    // TODO: parse server_real_time from body.

    callConnectedCb();
}

http::Request Client::createConnectReq(const char *device_id)
{
    using namespace http;

    char body_len[20];
    std::sprintf(body_len, "%lu", std::strlen(device_id));

    Request request(Request::POST, CONNECT_URL);
    HeaderOption hdr_option_host(HeaderOption::HOST, host);
    HeaderOption hdr_option_content_type(HeaderOption::CONTENT_TYPE, "text/plain");
    HeaderOption hdr_option_content_length(HeaderOption::CONTENT_LENGTH, body_len);
    Header hdr;
    hdr.appendOption(hdr_option_host);
    hdr.appendOption(hdr_option_content_type);
    hdr.appendOption(hdr_option_content_length);
    request.appendHeader(hdr);

    // TODO: encrypted body
    request.appendBody(device_id);

    return request;
}

void Client::callConnectedCb()
{
    if (clientCbRecver != nullptr) {
        clientCbRecver->connectedCb();
    }
}

void Client::callTempSentCb()
{
    if (clientCbRecver != nullptr) {
        clientCbRecver->tempSentCb();
    }
}

void Client::callIntervalsSentCb()
{
    if (clientCbRecver != nullptr) {
        clientCbRecver->intervalsSentCb();
    }
}

void Client::callIntervalsRecvCb(const IntervalList &interval_list)
{
    if (clientCbRecver != nullptr) {
        clientCbRecver->intervalsRecvCb(interval_list);
    }
}

} // namespace comm
