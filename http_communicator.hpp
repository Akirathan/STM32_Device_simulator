//
// Created by mayfa on 7.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTP_COMMUNICATOR_HPP
#define HTTP_COMMUNICATOR_HTTP_COMMUNICATOR_HPP

#define HTTP_COMMUNICATOR_HOST_LEN   30

#include <cstddef>
#include "string.hpp"

namespace http {

/**
 * Static class.
 */
class HttpCommunicator {
public:
    static void init(const char *host, const size_t host_len);
    static void connectDevice(const char *device_id, const size_t dev_len);

private:
    static const char *CONNECT_URL = "/connect/";
    static char host[HTTP_COMMUNICATOR_HOST_LEN];
    static bool initialized;
};

} // namespace

#endif //HTTP_COMMUNICATOR_HTTP_COMMUNICATOR_HPP
