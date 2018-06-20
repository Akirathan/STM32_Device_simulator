//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_DEVICE_HPP
#define DEVICE_SIMULATOR_DEVICE_HPP

#include <string>
#include "communication/interval_list.hpp"
#include "communication/i_client_cb_recver.hpp"

/**
 * Represents one STM device. Time synchronization is not simulated.
 * Newly set intervals are sent just once.
 *
 * Does not handle timestamps of temperature.
 */
class Device : public comm::IClientCbRecver {
private:
    static const size_t KEY_LEN = 9;

public:
    static const size_t ID_LEN = 15;

    Device(const char *id, const char *key);
    /***************** Getters and setters *********************/
    const char * getKey() const;
    const char * getId() const;
    bool isConnected() const;
    double getTemp() const;
    void setTemp(double temp);
    void setIntervals(const comm::IntervalList &interval_list);
    const comm::IntervalList & getIntervals() const;
    /***********************************************************/
    /*************** Callbacks from client *********************/
    void connectedCb() override;
    void tempSentCb() override;
    void intervalsSentCb() override;
    void intervalsRecvCb(const comm::IntervalList &interval_list) override;
    /***********************************************************/
    bool connect();
    void disconnect();

private:
    char key[KEY_LEN];
    char id[ID_LEN];
    double temp;
    uint32_t tempTimestamp;
    comm::IntervalList intervalList;
    bool connected;

    uint32_t getCurrentTimestamp() const;
};


#endif //DEVICE_SIMULATOR_DEVICE_HPP
