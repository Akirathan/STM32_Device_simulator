//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTPMESSAGE_HPP
#define HTTP_COMMUNICATOR_HTTPMESSAGE_HPP


#include <cstddef>
#include <cstdint>
#include "body.hpp"
#include "header_option.hpp"
#include "header.hpp"

namespace http {

class Request {
private:
    static const size_t URL_MAX_SIZE = 40;
    static const size_t TYPE_MAX_SIZE = 4;

public:
	static const size_t TOTAL_SIZE = URL_MAX_SIZE + TYPE_MAX_SIZE + Header::MAX_SIZE + Body::MAX_SIZE;

	enum method_t {
		GET,
		POST
	};

	Request(method_t method, const char *url);
	size_t getSize() const;
	void appendHeader(const Header &header);
	void appendBody(const uint8_t *buff, const size_t buff_size);
    void toBuffer(char *buffer) const;

private:
    method_t method;
	char url[URL_MAX_SIZE];
    const char *version;
	Header header;
	uint8_t body[Body::MAX_SIZE];
    size_t bodyLen;

	size_t getFirstLineSize() const;
	void firstLineToBuffer(char *buffer) const;
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTPMESSAGE_HPP
