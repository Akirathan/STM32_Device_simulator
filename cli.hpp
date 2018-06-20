//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_CLI_HPP
#define DEVICE_SIMULATOR_CLI_HPP

#include <string>
#include <vector>
#include "device.hpp"
#include "communication/interval_list.hpp"

class Cli {
public:
    Cli(Device &device);
    void poll();
private:
    Device & device;

    void printHelp() const;
    void parseCommand(const std::string &line);
    void parseSetIntervalsCommand(const std::vector<std::string> &line_items);
    std::vector<std::string> splitLine(const std::string &line) const;
    uint32_t parseTime(const std::string &str);

    void connectDevice();
    void disconnectDevice();
    void setTemperature(double temp);
    void setIntervals(const comm::IntervalList &interval_list);
    void getTemperature();
    void getIntervals();
};

#endif //DEVICE_SIMULATOR_CLI_HPP
