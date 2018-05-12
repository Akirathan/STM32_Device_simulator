//
// Created by mayfa on 8.5.18.
//

#include "request.hpp"

#include <cstring>
#include "../rt_assert.h"

namespace http {

Request::Request(Request::method_t method, const char *url) :
        Request()
{
	const char *method_str = nullptr;
	switch (method) {
		case GET:
			method_str = "GET";
			break;
		case POST:
			method_str = "POST";
			break;
	}

	size_t method_str_len = std::strlen(method_str);
	size_t url_len = std::strlen(url);
	rt_assert(method_str_len + 1 + url_len <= HTTP_MESSAGE_LEN, "Request: buffer overflow");

	memcpy(content, method_str, method_str_len);
	contentIdx += method_str_len;
	memcpy(content + contentIdx, url, url_len);
	contentIdx += url_len;
}

size_t Request::getSize() const
{
	return contentIdx;
}

void Request::appendHeader(const Header &header)
{
	header.toBuffer(content);
	contentIdx += header.getTotalSize();
}

void Request::appendBody(const char *value)
{
	size_t value_len = std::strlen(value);
	rt_assert(contentIdx + value_len + 2 <= HTTP_MESSAGE_LEN, "Request: buffer overflow");

	memcpy(content + contentIdx, value, value_len);
	contentIdx += value_len;
	content[contentIdx++] = '\r';
	content[contentIdx++] = '\n';
}

Request::Request() :
		contentIdx(0)
{
	for (size_t i = 0; i < HTTP_MESSAGE_LEN; ++i) {
		content[i] = 0;
	}
}

} // namespace http
