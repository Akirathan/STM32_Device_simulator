//
// Created by mayfa on 14.5.18.
//

#include "device.hpp"
#include <cstring>
#include <iostream>
#include "communication/client.hpp"

Device::Device(const char *id, const char *key) :
        temp(0.0),
        connected(false)
{
    std::strcpy(this->id, id);
    std::strcpy(this->key, key);
}

const char *Device::getKey() const
{
    return key;
}

const char *Device::getId() const
{
    return id;
}

/**
 * Sets the device temperature. Note that this temperature is periodically sent
 * to the server if this device is connected.
 * @note timestamp of temperature is always 0.
 * @param temp ... temperature to set.
 */
void Device::setTemp(double temp)
{
    this->temp = temp;
    if (connected) {
        comm::Client::setTemperature(temp, 0);
    }
}

/**
 * Note that Device must be connected so the intervals are communicated with server.
 */
void Device::setIntervals(const comm::IntervalList &interval_list)
{
    intervalList = interval_list;
    if (connected) {
        comm::Client::setIntervals(interval_list);
    }
}

/**
 * Sets connected state of the device ie. it is connected to the server.
 */
void Device::connectedCb()
{
    connected = true;
    std::cout << "Device: connectedCb" << std::endl;
}

void Device::tempSentCb()
{
    std::cout << "Device: tempSentCb" << std::endl;
}

void Device::intervalsSentCb()
{
    std::cout << "Device: intervalsSentCb" << std::endl;
}

void Device::intervalsRecvCb(const comm::IntervalList &interval_list)
{
    std::cout << "Device: intervalsReceiveCb" << std::endl;
}

/**
 * Sends connect request to server.
 * @return
 */
bool Device::connect()
{
    return comm::Client::sendConnectReq(id);
}


