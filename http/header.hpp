//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTP_HEADER_HPP
#define HTTP_COMMUNICATOR_HTTP_HEADER_HPP

#include "header_option.hpp"

namespace http {

/**
 * Represents HTTP header
 * May be empty ie. contain zero HeaderOptions.
 */
class Header {
private:
    static const size_t MAX_OPTIONS = 10;

public:
    static const size_t MAX_SIZE = MAX_OPTIONS * HeaderOption::MAX_SIZE;

	Header();
	void appendOption(const HeaderOption &option);

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
	HeaderOption options[MAX_OPTIONS];
	size_t optionsIdx;
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTP_HEADER_HPP
