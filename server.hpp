//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_SERVER_HPP
#define DEVICE_SIMULATOR_SERVER_HPP

#include <string>

/**
 * Serves just as save area for IP address and port
 */
class Server {
public:
    static std::string ipAddr;
    static uint16_t port;
};

#endif //DEVICE_SIMULATOR_SERVER_HPP
