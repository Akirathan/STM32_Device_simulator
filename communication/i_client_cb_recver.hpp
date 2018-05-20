//
// Created by mayfa on 20.5.18.
//

#ifndef DEVICE_SIMULATOR_I_CLIENT_CB_RECVER_HPP
#define DEVICE_SIMULATOR_I_CLIENT_CB_RECVER_HPP

#include "interval_list.hpp"

namespace comm {

/**
 * Interface for client callbacks receivers.
 */
class IClientCbRecver {
public:
    virtual void connectedCb() {}
    virtual void tempSentCb() {}
    virtual void intervalsSentCb() {}
    virtual void intervalsRecvCb(const IntervalList &interval_list) {}
};

} // namespace comm

#endif //DEVICE_SIMULATOR_I_CLIENT_CB_RECVER_HPP
