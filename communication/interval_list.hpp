//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_INTERVAL_LIST_HPP
#define DEVICE_SIMULATOR_INTERVAL_LIST_HPP

#include <cstddef>
#include <cstdint>
#include "interval.hpp"

namespace comm {

class IntervalList {
public:
    static const size_t MAX_NUM = 20;

    static IntervalList deserialize(const uint8_t *buffer, const size_t buff_size);

    IntervalList();
    void setTimestamp(uint32_t time_stamp);
    void addInterval(const Interval &interval);
    void serialize(uint8_t *buffer, size_t *size) const;

private:
    Interval intervals[MAX_NUM];
    size_t intervalsIdx;
    uint32_t timeStamp;
};

} // namespace comm

#endif //DEVICE_SIMULATOR_INTERVAL_LIST_HPP
