//
// Created by mayfa on 14.5.18.
//

#include <cstddef>
#include "interval.hpp"
#include "rt_assert.h"

namespace comm {

Interval Interval::deserialize(const uint8_t *buffer, const size_t buff_size)
{
    rt_assert(buff_size == SIZE, "Interval: wrong size of buffer");

    uint16_t from_time = *((const uint16_t *) buffer);
    buffer += 2;
    uint16_t to_time = *((const uint16_t *) buffer);
    buffer += 2;
    uint16_t temp = *((const uint16_t *) buffer);
    return Interval(from_time, to_time, temp);
}

Interval::Interval(const uint16_t fromTime, const uint16_t toTime, const uint16_t temp) :
        fromTime(fromTime),
        toTime(toTime),
        temp(temp)
{}

Interval::Interval() :
        Interval(0, 0, 0)
{}

void Interval::serialize(uint8_t *buffer, size_t *size) const
{
    *((uint16_t *) buffer) = fromTime;
    buffer += 2;
    *((uint16_t *) buffer) = toTime;
    buffer += 2;
    *((uint16_t *) buffer) = temp;

    if (size != nullptr) {
        *size = SIZE;
    }
}

void Interval::setFromTime(const uint16_t fromTime)
{
    this->fromTime = fromTime;
}

void Interval::setToTime(const uint16_t toTime)
{
    this->toTime = toTime;
}

void Interval::setTemp(const uint16_t temp)
{
    this->temp = temp;
}

} // namespace comm
