//
// Created by mayfa on 8.5.18.
//

#include "header.hpp"
#include "../rt_assert.h"

namespace http {

Header::Header() :
		optionsIdx(0)
{}

void Header::appendOption(HeaderOption option)
{
	rt_assert(optionsIdx + 1 <= HTTP_HEADER_MAX_OPTIONS, "Header: too much options");
	options[optionsIdx++] = option;
}

const char *Header::getOptionValueByType(HeaderOption::Type type) const
{
	for (size_t i = 0; i < optionsIdx; ++i) {
		if (options[i].type == type) {
			return options[i].value;
		}
	}
	return nullptr;
}

size_t Header::getTotalSize() const
{
	size_t total_size = 0;
	for (size_t i = 0; i < optionsIdx; ++i) {
		total_size += options[i].getTotalSize();
	}
	return total_size + 2;
}

} // namespace http
