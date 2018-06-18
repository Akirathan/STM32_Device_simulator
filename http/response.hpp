//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTP_RESPONSE_HPP
#define HTTP_COMMUNICATOR_HTTP_RESPONSE_HPP

#include <cstddef>
#include <cstdint>
#include "header.hpp"
#include "body.hpp"

namespace http {

/**
 * Represents immutable HTTP response object.
 */
class Response {
public:
	enum status_code_t {
        NONE,
		FORBIDDEN,
		OK
	};

    Response();
    void setStatusCode(unsigned int status_code);
	status_code_t getStatusCode() const;
    void copyIntoBody(const uint8_t *buff, const size_t buff_size);
    void setHeader(const Header &header);
	size_t getBodySize() const;
	const uint8_t *getBody() const;
private:
	status_code_t statusCode;
    Header header;
	uint8_t body[Body::MAX_SIZE];
    size_t bodySize;

    status_code_t convertStatusCode(unsigned int code);
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTP_RESPONSE_HPP
