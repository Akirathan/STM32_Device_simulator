//
// Created by mayfa on 14.5.18.
//

#include "client.hpp"
#include "http/response_parser.hpp"

namespace comm {


void Client::receiveCb(const uint8_t *buff, const size_t buff_size)
{
    switch (state) {
        case AWAIT_CONNECT_RESPONSE:
            http::Response response;
            if (!readResponse(buff, buff_size, &response)) {

            }
            break;
        case AWAIT_INTERVAL_TIMESTAMP_RESPONSE:break;
        case AWAIT_INTERVALS:break;
        case AWAIT_INTERVALS_ACK:break;
        case AWAIT_TEMP_ACK:break;
    }
}

/**
 *
 * @param response [out]
 * @return bool whether parsing succeed
 */
bool Client::readResponse(const uint8_t *buff, const size_t buff_size, http::Response *response)
{
    return http::ResponseParser::parse(static_cast<const char *>(buff), buff_size, response);
}

} // namespace comm
