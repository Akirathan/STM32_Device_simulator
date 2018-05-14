//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_INTERVAL_HPP
#define DEVICE_SIMULATOR_INTERVAL_HPP

#include <cstdint>

namespace comm {

class Interval {
public:
    static Interval deserialize(const uint8_t *buffer);

    Interval();
    Interval(const uint32_t fromTime, const uint32_t toTime, const uint32_t temp);
    void serialize(uint8_t *buffer) const;
    void setFromTime(const uint32_t fromTime);
    void setToTime(const uint32_t toTime);
    void setTemp(const uint32_t temp);

private:
    uint32_t fromTime;
    uint32_t toTime;
    uint32_t temp;
};

} // namespace comm

#endif //DEVICE_SIMULATOR_INTERVAL_HPP
