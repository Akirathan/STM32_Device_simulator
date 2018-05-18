//
// Created by mayfa on 14.5.18.
//

#include "interval_list.hpp"
#include "rt_assert.h"

namespace comm {

IntervalList IntervalList::deserialize(const uint8_t *buffer, const size_t buff_size)
{
    rt_assert(buff_size % Interval::SIZE == 0, "IntervalList: wrong size of buffer");

    IntervalList interval_list;
    for (int buff_idx = 0; buff_idx < buff_size; buff_idx += Interval::SIZE) {
        Interval interval = Interval::deserialize(buffer + buff_idx, Interval::SIZE);
        interval_list.addInterval(interval);
    }

    return interval_list;
}

IntervalList::IntervalList() :
        intervalsIdx(0),
        timeStamp(0)
{}

void IntervalList::setTimestamp(uint32_t time_stamp)
{
    timeStamp = time_stamp;
}

void IntervalList::addInterval(const Interval &interval)
{
    rt_assert(intervalsIdx <= MAX_NUM, "IntervalList: too much intervals");
    intervals[intervalsIdx++] = interval;
}

/**
 * Serializes this IntervalList into given buffer.
 *
 * @param buffer     ... buffer to serialize this IntervalList in.
 * @param size [out] ... number of filled bytes into buffer.
 */
void IntervalList::serialize(uint8_t *buffer, size_t *size) const
{
    size_t buff_idx = 0;
    for (size_t i = 0; i < intervalsIdx; ++i) {
        size_t interval_size = 0;
        intervals[i].serialize(buffer + buff_idx, &interval_size);
        buff_idx += interval_size;
    }

    if (size != nullptr) {
        *size = buff_idx;
    }
}


} // namespace comm