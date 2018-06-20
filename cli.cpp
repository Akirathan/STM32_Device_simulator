//
// Created by mayfa on 14.5.18.
//

#include <poll.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "cli.hpp"

using namespace std;

Cli::Cli(Device &device) :
    device(device)
{

}

void Cli::poll()
{
    struct pollfd poll_fd = {0, POLLIN, 0};
    if (::poll(&poll_fd, 1, 0) > 0) {
        string line;
        getline(cin, line);
        parseCommand(line);
    }
}

void Cli::printHelp() const
{
    cout << "known commands:" << endl
              << "  connect" << endl
              << "  disconnect" << endl
              << "  set temp <temperature>" << endl
              << "  set intervals <intervals>" << endl
              << "  get temp" << endl
              << "  get intervals" << endl;
}

void Cli::parseCommand(const string &line)
{
    vector<string> line_items = splitLine(line);
    if (line_items[0] == "connect") {
        connectDevice();
    }
    else if (line_items[0] == "disconnect") {
        disconnectDevice();
    }
    else if (line_items[0] == "set" && line_items[1] == "temp") {
        double temp = stod(line_items[2], nullptr);
        setTemperature(temp);
    }
    else if (line_items[0] == "set" && line_items[1] == "intervals") {
    }
}

vector<string> Cli::splitLine(const string &line) const
{
    istringstream istringstream(line);
    vector<string> line_items;

    do {
        string item;
        istringstream >> item;
        line_items.push_back(item);
    }
    while (istringstream);

    return line_items;
}

void Cli::connectDevice()
{
    if (!device.connect()) {
        cerr << "Error: device could not connect to the server" << endl;
    }
    else {
        cout << "Device connect to the server" << endl;
    }
}

void Cli::disconnectDevice()
{
    device.disconnect();
    cout << "Device disconnected" << endl;
}

void Cli::setTemperature(double temp)
{
    device.setTemp(temp);
    cout << "Temperature set" << endl;
}

