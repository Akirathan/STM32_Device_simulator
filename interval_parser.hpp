//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_INTERVAL_PARSER_HPP
#define DEVICE_SIMULATOR_INTERVAL_PARSER_HPP

#include "communication/interval_list.hpp"

class IntervalParser {
public:
    static comm::IntervalList parseIntervals(const char *str);

private:
    static comm::Interval parseInterval(const char *str, size_t *interval_size);
};


#endif //DEVICE_SIMULATOR_INTERVAL_PARSER_HPP
