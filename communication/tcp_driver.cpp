/**
 * @file tcp_driver.cpp
 * @brief TCP driver implemented with BSD sockets.
 */

#include "tcp_driver.hpp"
#include "rt_assert.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <cstdio>

namespace comm {

void TcpDriver::connect(const char *ip_addr, const uint16_t port)
{
    struct addrinfo hints;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    char port_str[7];
    std::sprintf(port_str, "%d", port);
    struct addrinfo *res;
    getaddrinfo(ip_addr, port_str, &hints, &res);

    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(socketFd, res->ai_addr, res->ai_addrlen) != 0) {
        std::fprintf(stderr, "connect");
    }

    connected = true;
}

bool TcpDriver::send(const uint8_t *buff, const size_t buff_len)
{
    rt_assert(connected, "TcpDriver: not connected");
    ssize_t sent = ::send(socketFd, buff, buff_len, 0);
    return sent == buff_len;
}

} // namespace comm
