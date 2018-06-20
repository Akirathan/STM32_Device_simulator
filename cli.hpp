//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_CLI_HPP
#define DEVICE_SIMULATOR_CLI_HPP

#include <string>
#include <vector>
#include "device.hpp"

class Cli {
public:
    Cli(Device &device);
    void poll();
private:
    Device & device;

    void printHelp() const;
    void parseCommand(const std::string &line);
    std::vector<std::string> splitLine(const std::string &line) const;

    void connectDevice();
    void disconnectDevice();
    void setTemperature(double temp);
};

#endif //DEVICE_SIMULATOR_CLI_HPP
