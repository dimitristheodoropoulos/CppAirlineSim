#pragma once
#include <vector>
#include <string>
#include <mutex>
#include "Assignment.h"

class Scheduler {
private:
    std::vector<Assignment> assignments;
    mutable std::mutex mtx;

public:
    Scheduler();

    void addAssignment(const Assignment& assignment);
    void removeAssignment(int flightId);
    void clearAssignments();
    std::vector<Assignment> getAssignments() const;
    size_t getAssignmentsCount() const;

    static int timeToMinutes(const std::string& timeStr);
};
