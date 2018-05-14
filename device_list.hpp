//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_DEVICE_LIST_HPP
#define DEVICE_SIMULATOR_DEVICE_LIST_HPP


#include <memory>
#include <vector>
#include "device.hpp"

class DeviceList {
public:
    Device & getDeviceById(const std::string &device_id);
    void addDevice(std::unique_ptr<Device> device);

private:
    std::vector<std::unique_ptr<Device>> devices;
};


#endif //DEVICE_SIMULATOR_DEVICE_LIST_HPP
