//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTP_HEADER_HPP
#define HTTP_COMMUNICATOR_HTTP_HEADER_HPP

#include "header_option.hpp"
#include "response_parser.hpp"

namespace http {

class Header {
public:
	Header();
	void appendOption(HeaderOption option);

	/**
	 * @param type
	 * @return ... nullptr if no such option was found.
	 */
	const char *getOptionValueByType(HeaderOption::Type type) const;

	/**
	 * Returns total size of this header including trailing linebreak.
	 */
	size_t getTotalSize() const;
	void toBuffer(char *buffer) const;

private:
	HeaderOption options[HTTP_HEADER_MAX_OPTIONS];
	size_t optionsIdx;
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTP_HEADER_HPP
