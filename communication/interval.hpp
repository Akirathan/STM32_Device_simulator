//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_INTERVAL_HPP
#define DEVICE_SIMULATOR_INTERVAL_HPP

#include <cstdint>

namespace comm {

class Interval {
public:
    static const size_t SIZE = 6;

    static Interval deserialize(const uint8_t *buffer, const size_t buff_size);

    Interval(const uint16_t fromTime, const uint16_t toTime, const uint16_t temp);
    Interval();
    void serialize(uint8_t *buffer, size_t *size) const;
    void setFromTime(const uint16_t fromTime);
    void setToTime(const uint16_t toTime);
    void setTemp(const uint16_t temp);

private:
    uint16_t fromTime;
    uint16_t toTime;
    uint16_t temp;
};

} // namespace comm

#endif //DEVICE_SIMULATOR_INTERVAL_HPP
