//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTP_RESPONSE_HPP
#define HTTP_COMMUNICATOR_HTTP_RESPONSE_HPP

#include <cstddef>

namespace http {

class Response {
public:
	enum status_code_t {
		FORBIDDEN,
		OK
	} statusCode;

	unsigned long getBodySize() const;
	const char *getBody() const;
private:
	const char *body;
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTP_RESPONSE_HPP
