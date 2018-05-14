//
// Created by mayfa on 14.5.18.
//

#ifndef DEVICE_SIMULATOR_CLI_HPP
#define DEVICE_SIMULATOR_CLI_HPP

#include <string>

class Cli {
public:
    static void processCommand(const std::string &str, DeviceList &dev_list);
};

#endif //DEVICE_SIMULATOR_CLI_HPP
