//
// Created by mayfa on 7.5.18.
//

#include "http_communicator.hpp"
#include <cstring>

namespace http {

void HttpCommunicator::init(const char *host, const size_t host_len) {
	std::memcpy(HttpCommunicator::host, host, host_len);
	initialized = true;
}

void HttpCommunicator::connectDevice(const char *device_id, const size_t dev_len) {

}

} // namespace http
