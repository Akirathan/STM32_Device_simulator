//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTPMESSAGE_HPP
#define HTTP_COMMUNICATOR_HTTPMESSAGE_HPP

#define HTTP_MESSAGE_LEN      40

#include <cstddef>
#include "header_option.hpp"
#include "header.hpp"

namespace http {

class Request {
public:
	enum method_t {
		GET,
		POST
	};

	Request(method_t method, const char *url);
	size_t getSize() const;
	/**
	 * Appends given header into content.
	 */
	void appendHeader(const Header &header);
	void appendBody(const char *value);
private:
	Request();
	char content[HTTP_MESSAGE_LEN];
	size_t contentIdx;
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTPMESSAGE_HPP
