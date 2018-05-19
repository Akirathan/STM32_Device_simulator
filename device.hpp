//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_DEVICE_HPP
#define DEVICE_SIMULATOR_DEVICE_HPP

#include <string>
#include "communication/interval_list.hpp"

class Device {
private:
    static const size_t KEY_LEN = 9;
    static const size_t ID_LEN = 15;

public:
    Device(const char *id, const char *key);
    const char * getKey() const;
    uint32_t getTemp() const;
    void setTemp(uint32_t temp);
    void setIntervals(const comm::IntervalList &interval_list);
    const comm::IntervalList & getIntervals() const;
    void setConnected();
    bool connect();

private:
    char key[KEY_LEN];
    char id[ID_LEN];
    uint32_t temp;
    comm::IntervalList intervalList;
    bool connected;
};


#endif //DEVICE_SIMULATOR_DEVICE_HPP
