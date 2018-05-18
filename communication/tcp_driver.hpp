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
    static void connect(const char *ip_addr, const uint16_t port);
    static bool send(const uint8_t *buff, const size_t buff_len);

private:
    static int socketFd;
    static bool connected;
};

} // namespace comm

#endif //DEVICE_SIMULATOR_TCP_DRIVER_HPP_HPP
