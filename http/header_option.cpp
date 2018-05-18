//
// Created by mayfa on 8.5.18.
//

#include <cstring>
#include "header_option.hpp"

namespace http {

HeaderOption::HeaderOption() :
        type(UNKNOWN_TYPE)
{}

HeaderOption::HeaderOption(HeaderOption::Type type, const char *value) :
        type(type)
{
    std::strcpy(this->value, value);
}

/**
 * Returns total size including white spaces.
 */
size_t HeaderOption::getTotalSize() const
{
	return getTypeSize() + 1 + getValueSize() + 2;
}

/**
 * Copies this HttpHeaderOption into given buffer from given index without
 * trailing linebreak.
 * @param buffer     ... buffer into which this option will copy itself.
 * @param buffer_idx ... from which buffer index should this option copy.
 */
void HeaderOption::toBuffer(char *buffer) const
{
    const char *type_str = nullptr;
    switch (type) {
        case UNKNOWN_TYPE:
            break;
        case CONTENT_TYPE:
            type_str = CONTENT_TYPE_STR;
            break;
        case CONTENT_LENGTH:
            type_str = CONTENT_LENGTH_STR;
            break;
        case HOST:
            type_str = HOST_STR;
            break;
    }
    std::strcpy(buffer, type_str);
    buffer += std::strlen(type_str);

    *(buffer++) = ':';
    std::strcpy(buffer, value);
    buffer += std::strlen(value);
    *(buffer++) = '\r';
    *(buffer++) = '\n';
    *buffer = '\0';
}

size_t HeaderOption::getTypeSize() const
{
	switch (type) {
		case CONTENT_TYPE:
			return std::strlen(CONTENT_TYPE_STR);
		case CONTENT_LENGTH:
			return std::strlen(CONTENT_LENGTH_STR);
        case HOST:
            return std::strlen(HOST_STR);
        default:
            return 0;
    }
}

size_t HeaderOption::getValueSize() const
{
	return std::strlen(value);
}

void HeaderOption::setType(HeaderOption::Type type)
{
    this->type = type;
}

HeaderOption::Type HeaderOption::getType() const
{
	return type;
}

void HeaderOption::setValue(const char *newValue)
{
    std::strcpy(value, newValue);
}

const char *HeaderOption::getValue() const
{
    return value;
}


} // namespace http