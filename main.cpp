#include <cstring>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <sstream>
#include "http/response_buffer.hpp"
#include "http/request.hpp"
#include "communication/interval.hpp"
#include "communication/client.hpp"
#include "communication/tcp_driver.hpp"
#include "device.hpp"
#include "cli.hpp"

using namespace http;
using namespace comm;
using namespace std;

void parse_request()
{
    const char *message = "HTTP/1.1 200 OK\r\nDate: Sun,20 May 2018 12:52:36 GMT\r\n\r\n580";
    const size_t message_len = std::strlen(message);

    http::ResponseBuffer::awaitBody();
    http::ResponseBuffer::buff(reinterpret_cast<const uint8_t *>(message), message_len);

    exit(0);
}

int main(int argc, char *args[])
{
    // TODO: add key argument
    if (argc != 2) {
        cerr << "Wrong number of arguments" << endl;
        exit(1);
    }

    Device device(args[1], "key");
    ResponseBuffer::init();
    Client::init("127.0.0.1", 8000, &device);
    TcpDriver::init("127.0.0.1", 8000);

    Cli cli(device);
    while (true) {
        if (device.isConnected()) {
            TcpDriver::poll();
        }
        cli.poll();
    }
}