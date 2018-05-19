//
// Created by mayfa on 8.5.18.
//

#include <cstring>
#include "response.hpp"

namespace http {

Response::Response() :
        statusCode(NONE),
        body(nullptr)
{}

void Response::setStatusCode(unsigned int status_code)
{
    statusCode = convertStatusCode(status_code);
}

Response::status_code_t Response::getStatusCode() const
{
    return statusCode;
}

void Response::copyIntoBody(const char *newBody)
{
    std::strcpy(body, newBody);
}

void Response::setHeader(const Header &header)
{
    this->header = header;
}

/**
 * Converts given int code into @ref status_code_t and saves it into private data member.
 * @param code
 */
Response::status_code_t Response::convertStatusCode(unsigned int code)
{
    status_code_t ret_val = NONE;
    if (code == 200) {
        ret_val = OK;
    }
    else if (code == 404) {
        ret_val = FORBIDDEN;
    }
    return ret_val;
}



} // namespace http
