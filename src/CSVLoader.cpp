#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

// trim spaces και \r\n
static std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    auto end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

std::vector<Aircraft> CSVLoader::loadAircraft(const std::string& path) {
    std::vector<Aircraft> result;
    std::ifstream file(path);
    if (!file.is_open()) { 
        std::cerr << "Cannot open " << path << "\n"; 
        return result; 
    }

    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, model, capStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, model, ',');
        std::getline(ss, capStr, ',');

        idStr = trim(idStr);
        model = trim(model);
        capStr = trim(capStr);

        try {
            int id = std::stoi(idStr);
            int capacity = std::stoi(capStr);
            result.emplace_back(id, model, capacity);
        } catch (...) {
            continue;
        }
    }
    return result;
}

std::vector<Flight> CSVLoader::loadFlights(const std::string& path) {
    std::vector<Flight> result;
    std::ifstream file(path);
    if (!file.is_open()) { 
        std::cerr << "Cannot open " << path << "\n"; 
        return result; 
    }

    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, origin, destination, depTime, durStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, origin, ',');
        std::getline(ss, destination, ',');
        std::getline(ss, depTime, ',');
        std::getline(ss, durStr, ',');

        idStr = trim(idStr);
        origin = trim(origin);
        destination = trim(destination);
        depTime = trim(depTime);
        durStr = trim(durStr);

        try {
            int id = std::stoi(idStr);
            int duration = std::stoi(durStr);

            int depH, depM;
            char sep;
            std::istringstream depSS(depTime);
            depSS >> depH >> sep >> depM;

            if (depSS.fail() || sep != ':') {
                throw std::invalid_argument("Invalid time format");
            }

            int depMins = depH * 60 + depM;
            int arrMins = (depMins + duration) % (24 * 60);
            int arrH = arrMins / 60;
            int arrM = arrMins % 60;

            std::ostringstream depSSFixed, arrSSFixed;
            depSSFixed << std::setw(2) << std::setfill('0') << depH << ":" 
                       << std::setw(2) << std::setfill('0') << depM;
            arrSSFixed << std::setw(2) << std::setfill('0') << arrH << ":" 
                       << std::setw(2) << std::setfill('0') << arrM;

            // default flightNumber και airline
            std::string flightNumber = "FN" + std::to_string(id);
            std::string airline = "Unknown";

            result.emplace_back(id, flightNumber, depSSFixed.str(), arrSSFixed.str(), airline);
        } catch (...) {
            continue;
        }
    }
    return result;
}

std::vector<Crew> CSVLoader::loadCrew(const std::string& path) {
    std::vector<Crew> result;
    std::ifstream file(path);
    if (!file.is_open()) { 
        std::cerr << "Cannot open " << path << "\n"; 
        return result; 
    }

    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, role;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, role, ',');

        idStr = trim(idStr);
        name = trim(name);
        role = trim(role);

        try {
            int id = std::stoi(idStr);
            result.emplace_back(id, name, role);
        } catch (...) {
            continue;
        }
    }
    return result;
}
