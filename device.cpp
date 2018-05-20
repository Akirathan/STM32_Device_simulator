//
// Created by mayfa on 14.5.18.
//

#include "device.hpp"
#include <cstring>
#include <iostream>
#include "communication/client.hpp"

Device::Device(const char *id, const char *key) :
        temp(0),
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
 * Sets connected state of the device ie. it is connected to the server.
 */
void Device::connectedCb()
{
    connected = true;
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
    bool ret_val = false;
    ret_val = comm::Client::sendConnectReq(id);
}


