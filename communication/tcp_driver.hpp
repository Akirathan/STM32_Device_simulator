//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_TCP_DRIVER_HPP_HPP
#define DEVICE_SIMULATOR_TCP_DRIVER_HPP_HPP

#include <cstdint>
#include <cstddef>

namespace comm {

/**
 * Common driver declaration for both BSD socket and LwIP implementation.
 */
class TcpDriver {
public:
    static void init(const char *ip_addr, uint16_t port);
    static bool send(const uint8_t *buff, const size_t buff_len);
    static void poll();
    static void wholeMessageReceivedCb();

private:
    static const size_t IP_ADDR_LEN = 16;

    static int socketFd;
    static bool initialized;
    static char ipAddr[IP_ADDR_LEN];
    static uint16_t port;

    static void connect(const char *ip_addr, const uint16_t port);
    static void disconnect();
};

} // namespace comm

#endif //DEVICE_SIMULATOR_TCP_DRIVER_HPP_HPP
