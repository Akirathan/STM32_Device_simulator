//
// Created by mayfa on 14.5.18.
//

#include <poll.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "cli.hpp"
#include "communication/interval_list.hpp"
#include "communication/interval.hpp"

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
        line_items.erase(line_items.begin(), line_items.begin() + 1);
        parseSetIntervalsCommand(line_items);
    }
    else if (line_items[0] == "get" && line_items[1] == "temp") {
        getTemperature();
    }
    else if (line_items[0] == "get" && line_items[1] == "intervals") {
        getIntervals();
    }
    else {
        printHelp();
    }
}

void Cli::parseSetIntervalsCommand(const std::vector<std::string> &line_items)
{
    if (line_items.size() % 3 != 0) {
        cerr << "Wrong format of intervals" << endl;
        return;
    }

    comm::IntervalList interval_list;
    for (size_t i = 0; i < line_items.size(); i += 3) {
        uint32_t from_time = parseTime(line_items[0]);
        uint32_t to_time = parseTime(line_items[1]);
        uint32_t temp = static_cast<uint32_t>(stoul(line_items[2]));
        comm::Interval interval(from_time, to_time, temp);
        interval_list.addInterval(interval);
    }

    setIntervals(interval_list);
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

uint32_t Cli::parseTime(const std::string &str)
{
    istringstream iss(str);
    string hours;
    string minutes;
    getline(iss, hours, ':');
    getline(iss, minutes, ':');

    return static_cast<uint32_t>(stoul(hours, nullptr) + stoul(minutes, nullptr) * 60);
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

void Cli::setIntervals(const comm::IntervalList &interval_list)
{
    device.setIntervals(interval_list);
    cout << "Intervals set" << endl;
}

void Cli::getTemperature()
{
    cout << "Device temperature: " + to_string(device.getTemp()) << endl;
}

void Cli::getIntervals()
{
    cout << "Intervals: ";
    const comm::IntervalList &interval_list = device.getIntervals();
    for (size_t i = 0; i < interval_list.getIntervalsCount(); i++) {
        const comm::Interval *interval = interval_list.getInterval(i);

        int from_hours = interval->getFromTime() / 60 * 60;
        int from_minutes = interval->getFromTime() / 60;
        int to_hours = interval->getToTime() / 60 * 60;
        int to_minutes = interval->getToTime() / 60;

        cout << to_string(from_hours) << ":" << to_string(from_minutes) << " "
             << to_string(to_hours) << ":" << to_string(to_minutes) << " "
             << to_string(interval->getTemp()) << ",";
    }
    cout << endl;
}

