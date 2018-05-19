//
// Created by mayfa on 14.5.18.
//

#include <cstring>
#include "device.hpp"
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
void Device::setConnected()
{
    connected = true;
}

/**
 * Sends connect request to server.
 * @return
 */
bool Device::connect()
{
    bool ret_val = false;
    ret_val = comm::Client::sendConnectReq(this);
}


