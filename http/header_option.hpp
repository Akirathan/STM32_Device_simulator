//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTP_HEADER_OPTION_HPP
#define HTTP_COMMUNICATOR_HTTP_HEADER_OPTION_HPP

#include <cstddef>

namespace http {

/**
 * Represents one header option with line break.
 */
class HeaderOption {
public:
	enum Type {
		CONTENT_TYPE,
		CONTENT_LENGTH
	};
	Type type;
	const char *value;
	/**
	 * Returns total size including white spaces.
	 */
	size_t getTotalSize() const;
	/**
	 * Copies this HttpHeaderOption into given buffer from given index.
	 * @param buffer     ... buffer into which this option will copy itself.
	 * @param buffer_idx ... from which buffer index should this option copy.
	 */
	void toBuffer(char *buffer, size_t buffer_idx) const;

private:
	static const char *CONTENT_TYPE_STR = "Content-Type";
	static const char *CONTENT_LENGTH_STR = "Content-Length";

	size_t getTypeSize() const;
	size_t getValueSize() const;
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTP_HEADER_OPTION_HPP
