#include <cstring>
#include <cstdio>
#include "http/response_parser.hpp"
#include "http/request.hpp"
#include "communication/interval.hpp"

using namespace http;

void create_request()
{
    const char *message = "HTTP/1.1 200 OK\r\nContent-Length: 24";
    const size_t message_len = std::strlen(message);

    const char *body = "dev_id";
    char body_len[2];
    std::sprintf(body_len, "%u", static_cast<unsigned int>(std::strlen(body)));
    HeaderOption opt_len(HeaderOption::CONTENT_LENGTH, body_len);
    HeaderOption opt_content_type(HeaderOption::CONTENT_TYPE, "text/plain");
    Header hdr;
    hdr.appendOption(opt_len);
    hdr.appendOption(opt_content_type);

    Request request(Request::GET, "/connect");
    request.appendHeader(hdr);
    request.appendBody(body);

    char req_buffer[Request::TOTAL_SIZE];
    request.toBuffer(req_buffer);

    std::printf("%s", req_buffer);
}

int main()
{
    create_request();
}