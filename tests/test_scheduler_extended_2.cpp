#include "../data/include/Scheduler.h"
#include "../data/include/Assignment.h"
#include <gtest/gtest.h>
#include <vector>
#include <thread>
#include <algorithm>

TEST(SchedulerMultiThreadedTest, AddAssignmentsConcurrently) {
    Scheduler sched;

    std::vector<Assignment> thread1Assignments = {
        Assignment(101, 1),
        Assignment(102, 2),
        Assignment(103, 3)
    };

    std::vector<Assignment> thread2Assignments = {
        Assignment(201, 4),
        Assignment(202, 5),
        Assignment(203, 6)
    };

    auto worker = [&sched](const std::vector<Assignment>& assignments) {
        for (const auto& a : assignments) {
            sched.addAssignment(a); // thread-safe
        }
    };

    std::thread t1(worker, thread1Assignments);
    std::thread t2(worker, thread2Assignments);

    t1.join();
    t2.join();

    EXPECT_EQ(sched.getAssignmentsCount(), 6);

    auto allAssignments = sched.getAssignments();
    std::vector<int> expectedFlights = {101, 102, 103, 201, 202, 203};

    for (const auto& flight : expectedFlights) {
        auto it = std::find_if(allAssignments.begin(), allAssignments.end(),
                               [&](const Assignment& a){ return a.getFlightId() == flight; });
        EXPECT_NE(it, allAssignments.end());
    }
}
