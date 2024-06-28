#include "AmodeConfig.h"
#include <fstream>
#include <set>
#include <sstream>

AmodeConfig::AmodeConfig(const std::string& filename) {
    loadData(filename);
}

void AmodeConfig::loadData(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Skip the header row.

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> tmp_data;
        AmodeConfig::Data data;

        // Split the line by ';' and store in tmp_data.
        while (std::getline(ss, cell, ';')) {
            tmp_data.push_back(cell);
        }

        // Store the data properly to our Data
        data.number = std::stoi(tmp_data[0]);
        data.group  = std::stoi(tmp_data[1]);
        data.groupname = tmp_data[2];
        data.local_R   = {std::stod(tmp_data[3]), std::stod(tmp_data[4]),std::stod(tmp_data[5])};
        data.local_t   = {std::stod(tmp_data[6]), std::stod(tmp_data[7]),std::stod(tmp_data[8])};

        // Insert the data into the map.
        dataMap[data.number] = data;
    }
}

AmodeConfig::Data AmodeConfig::getDataByNumber(int number) const {
    auto it = dataMap.find(number);
    if (it != dataMap.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Data not found for the given number.");
    }
}

// Function to get all Data with the specified group name.
std::vector<AmodeConfig::Data> AmodeConfig::getDataByGroupName(const std::string& groupname) const {
    std::vector<Data> result;
    for (const auto& entry : dataMap) {
        if (entry.second.groupname == groupname) {
            result.push_back(entry.second);
        }
    }
    return result;
}

// Function to get all unique group names from dataMap.
std::vector<std::string> AmodeConfig::getAllGroupNames() const {
    std::set<std::string> groupNamesSet;
    for (const auto& entry : dataMap) {
        if (entry.second.groupname!="") groupNamesSet.insert(entry.second.groupname);
    }
    // Convert the set to a vector to return.
    return std::vector<std::string>(groupNamesSet.begin(), groupNamesSet.end());
}
