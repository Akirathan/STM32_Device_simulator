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
private:
    static const size_t VALUE_LEN = 50;
    static const size_t TYPE_LEN = 20;

public:
    static const size_t MAX_SIZE = TYPE_LEN + VALUE_LEN;
    static constexpr const char *CONTENT_TYPE_STR = "Content-Type";
    static constexpr const char *CONTENT_LENGTH_STR = "Content-Length";
    static constexpr const char *HOST_STR = "Host";

	enum Type {
        UNKNOWN_TYPE,
		CONTENT_TYPE,
		CONTENT_LENGTH,
		HOST
	};

	HeaderOption();
    HeaderOption(Type type, const char *value);
	size_t getTotalSize() const;
	void toBuffer(char *buffer) const;
	void setType(Type type);
    Type getType() const;
    void setValue(const char *newValue);
    const char * getValue() const;

private:
	Type type;
	char value[VALUE_LEN];

	size_t getTypeSize() const;
	size_t getValueSize() const;
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTP_HEADER_OPTION_HPP
