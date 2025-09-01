#include "Scheduler.h"
#include <algorithm>
#include <stdexcept>

Scheduler::Scheduler() = default;

void Scheduler::addAssignment(const Assignment& assignment) {
    std::lock_guard<std::mutex> lock(mtx);
    assignments.push_back(assignment);
}

void Scheduler::removeAssignment(int flightId) {
    std::lock_guard<std::mutex> lock(mtx);
    assignments.erase(
        std::remove_if(assignments.begin(), assignments.end(),
                       [&](const Assignment& a){ return a.getFlightId() == flightId; }),
        assignments.end()
    );
}

void Scheduler::clearAssignments() {
    std::lock_guard<std::mutex> lock(mtx);
    assignments.clear();
}

std::vector<Assignment> Scheduler::getAssignments() const {
    std::lock_guard<std::mutex> lock(mtx);
    return assignments;
}

size_t Scheduler::getAssignmentsCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return assignments.size();
}

int Scheduler::timeToMinutes(const std::string& timeStr) {
    if (timeStr.size() != 5 || timeStr[2] != ':')
        throw std::invalid_argument("Invalid time format");
    int h = std::stoi(timeStr.substr(0,2));
    int m = std::stoi(timeStr.substr(3,2));
    return h*60 + m;
}
