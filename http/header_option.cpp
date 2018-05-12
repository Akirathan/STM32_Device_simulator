//
// Created by mayfa on 8.5.18.
//

#include <cstring>
#include "header_option.hpp"

namespace http {

size_t HeaderOption::getTotalSize() const
{
	return getTypeSize() + 2 + getValueSize() + 2;
}

size_t HeaderOption::getTypeSize() const
{
	switch (type) {
		case CONTENT_TYPE:
			return std::strlen(CONTENT_TYPE_STR);
		case CONTENT_LENGTH:
			return std::strlen(CONTENT_LENGTH_STR);
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

	if (type == UNKNOWN_TYPE) {
		value = nullptr;
	}
}

HeaderOption::Type HeaderOption::getType() const
{
	return type;
}

void HeaderOption::copyIntoValue(const char *newValue)
{
    std::strcpy(value, newValue);
}

} // namespace http