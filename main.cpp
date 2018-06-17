#include <cstring>
#include <cstdio>
#include "http/response_buffer.hpp"
#include "http/request.hpp"
#include "communication/interval.hpp"
#include "communication/client.hpp"
#include "communication/tcp_driver.hpp"
#include "device.hpp"

using namespace http;
using namespace comm;

void parse_request()
{
    const char *message = "HTTP/1.1 200 OK\r\nDate: Sun,20 May 2018 12:52:36 GMT\r\n\r\n580";
    const size_t message_len = std::strlen(message);

    http::ResponseBuffer::awaitBody();
    http::ResponseBuffer::buff(reinterpret_cast<const uint8_t *>(message), message_len);

    exit(0);
}

int main()
{
    http::ResponseBuffer::init();
    Device device("stm1", "key");
    comm::Client::init("127.0.0.1", 8000, &device);
    comm::TcpDriver::init("127.0.0.1", 8000);
    if (!device.connect()) {
        std::printf("Connection failed");
    }

    while (true) {
        TcpDriver::poll();
    }
}