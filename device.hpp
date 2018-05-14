//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_DEVICE_HPP
#define DEVICE_SIMULATOR_DEVICE_HPP

#include <string>
#include "communication/interval_list.hpp"

class Device {
public:
    Device(const std::string &id, const std::string &key);
    bool connect();
    void setTemp(uint32_t temp);
    void setIntervals(const comm::IntervalList &interval_list);
    uint32_t getTemp() const;
    const comm::IntervalList & getIntervals() const;

private:
    std::string key;
    std::string id;
    uint32_t temp;
    comm::IntervalList intervalList;
};


#endif //DEVICE_SIMULATOR_DEVICE_HPP
