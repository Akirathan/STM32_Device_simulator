//
// Created by mayfa on 8.5.18.
//

#include "request.hpp"

#include <cstring>

namespace http {

Request::Request(Request::method_t method, const char *url) :
        method(method),
        version("HTTP/1.1")
{
    std::strcpy(this->url, url);

    for (size_t i = 0; i < Body::MAX_SIZE; ++i) {
        body[i] = '\0';
    }
}

size_t Request::getSize() const
{
	size_t size = 0;
    size += getFirstLineSize();
    size += header.getTotalSize();
    if (std::strlen(body) > 0) {
        // Empty line (delimiter) size + header size
        size += 2;
        size += std::strlen(body);
    }
    return size;
}

void Request::appendHeader(const Header &header)
{
    this->header = header;
}

void Request::appendBody(const char *value)
{
    std::strcpy(body, value);
}

void Request::toBuffer(char *buffer) const
{
    firstLineToBuffer(buffer);
    buffer += getFirstLineSize();
    header.toBuffer(buffer);
    buffer += header.getTotalSize();
    if (std::strlen(body) > 0) {
        *(buffer++) = '\r';
        *(buffer++) = '\n';
        std::strcpy(buffer, body);
    }
}

size_t Request::getFirstLineSize() const
{
    size_t size = 0;
	switch (method) {
        case GET:
            size += 3;
            break;
        case POST:
            size += 4;
            break;
    }
    size += 1;
    size += std::strlen(url);
    size += 1;
    size += std::strlen(version);
    // Add line break size \r\n
    size += 2;
    return size;
}

void Request::firstLineToBuffer(char *buffer) const
{
    switch(method) {
        case GET:
            std::strcpy(buffer, "GET");
            buffer += std::strlen("GET");
            break;
        case POST:
            std::strcpy(buffer, "POST");
            buffer += std::strlen("POST");
            break;
    }
    *(buffer++) = ' ';
    std::strcpy(buffer, url);
    buffer += std::strlen(url);

    *(buffer++) = ' ';
    std::strcpy(buffer, version);
    buffer += std::strlen(version);

    *(buffer++) = '\r';
    *(buffer++) = '\n';
    *buffer = '\0';
}

} // namespace http
