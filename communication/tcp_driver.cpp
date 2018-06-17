/**
 * @file tcp_driver.cpp
 * @brief TCP driver implemented with BSD sockets.
 */

#include "tcp_driver.hpp"
#include "rt_assert.h"
#include "client.hpp"
#include <sys/socket.h>
#include <poll.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include "http/response_buffer.hpp"

namespace comm {

int       TcpDriver::socketFd = 0;
bool      TcpDriver::initialized = false;
char      TcpDriver::ipAddr[IP_ADDR_LEN];
uint16_t  TcpDriver::port = 0;

void TcpDriver::init(const char *ip_addr, uint16_t port)
{
    std::strcpy(ipAddr, ip_addr);
    TcpDriver::port = port;
    initialized = true;
}

/**
 * Supposes that connection must be established every time client want to send something.
 * @param buff
 * @param buff_len
 * @return
 */
bool TcpDriver::send(const uint8_t *buff, const size_t buff_len)
{
    connect(ipAddr, port);
    ssize_t sent = ::send(socketFd, buff, buff_len, 0);
    disconnect();
    
    return sent == buff_len;
}

/**
 * Specific for BSD socket API.
 */
void TcpDriver::poll()
{
    struct pollfd poll_fd = {socketFd, POLLIN, 0};
    if (::poll(&poll_fd, 1, 0) > 0) {
        uint8_t buff[512];
        size_t read_num = 0;
        do {
            read_num = static_cast<size_t>(read(socketFd, buff, 512));
            if (read_num > 0) {
                http::ResponseBuffer::buff(buff, read_num);
            }
        }
        while (read_num > 0);
    }
}

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
    if (::connect(socketFd, res->ai_addr, res->ai_addrlen) != 0) {
        std::fprintf(stderr, "connect");
    }
}

void TcpDriver::disconnect()
{
    close(socketFd);
}

} // namespace comm
