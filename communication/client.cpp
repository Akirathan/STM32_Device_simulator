//
// Created by mayfa on 14.5.18.
//

#include "client.hpp"
#include "http/response_parser.hpp"
#include "tcp_driver.hpp"

namespace comm {

bool                  Client::initialized = false;
char                  Client::ipAddr[IP_ADDR_LEN];
uint16_t              Client::port = 0;
char                  Client::host[HOST_LEN];
Client::await_state_t Client::state = AWAIT_NONE;
Device *              Client::currDevice = nullptr;

void Client::init(const char *ip_addr, uint16_t port)
{
    if (!initialized) {
        std::strcpy(ipAddr, ip_addr);
        Client::port = port;
        initHost(ip_addr, port);
        initialized = true;
    }
}

void Client::receiveCb(const uint8_t *buff, const size_t buff_size)
{
    switch (state) {
        case AWAIT_CONNECT_RESPONSE:
            readConnectResponse(buff, buff_size);
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
 * @param device  ... pointer to device that will be notified when connection is
 *                    successfull.
 * @return false when TCPDriver fails to send data.
 */
bool Client::sendConnectReq(Device *device)
{
    currDevice = device;
    TcpDriver::connect(ipAddr, port);

    http::Request req = createConnectReq(device);
    char buffer[http::Request::TOTAL_SIZE];
    req.toBuffer(buffer);
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
 *
 * @param response [out]
 * @return bool whether parsing succeed
 */
bool Client::readResponse(const uint8_t *buff, const size_t buff_size, http::Response *response)
{
    return http::ResponseParser::parse(reinterpret_cast<const char *>(buff), buff_size, response);
}

/**
 * Response from server should contain server_real_time in body.
 * @param buff      ... received buffer from server.
 * @param buff_size ... received buffer size.
 */
void Client::readConnectResponse(const uint8_t *buff, const size_t buff_size)
{
    http::Response response;
    if (!readResponse(buff, buff_size, &response)) {
        // Send connected request again
        // TODO: error handling
        sendConnectReq(currDevice);
        return;
    }

    if (response.getStatusCode() != http::Response::OK) {
        // ...
        return;
    }

    // TODO: parse server_real_time from body.

    currDevice->setConnected();
    currDevice = nullptr;
}

http::Request Client::createConnectReq(const Device *device)
{
    using namespace http;

    Request request(Request::GET, CONNECT_URL);
    HeaderOption hdr_option_host(HeaderOption::HOST, host);
    Header hdr;
    hdr.appendOption(hdr_option_host);
    request.appendHeader(hdr);

    // TODO: encrypted body
    request.appendBody(device->getId());

    return request;
}



} // namespace comm
