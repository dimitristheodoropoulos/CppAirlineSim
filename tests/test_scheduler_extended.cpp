#include "../data/include/Scheduler.h"
#include "../data/include/Assignment.h"
#include <gtest/gtest.h>
#include <vector>

TEST(SchedulerExtendedTest, MultipleAssignments) {
    Scheduler sched;

    Assignment a1(101, 1);
    Assignment a2(102, 2);
    Assignment a3(103, 3);

    sched.addAssignment(a1);
    sched.addAssignment(a2);
    sched.addAssignment(a3);

    EXPECT_EQ(sched.getAssignmentsCount(), 3);

    auto assignments = sched.getAssignments();
    ASSERT_EQ(assignments.size(), 3);
    EXPECT_EQ(assignments[0].getFlightId(), 101);
    EXPECT_EQ(assignments[1].getFlightId(), 102);
    EXPECT_EQ(assignments[2].getFlightId(), 103);
}

TEST(SchedulerExtendedTest, RemoveSpecificAssignment) {
    Scheduler sched;

    sched.addAssignment(Assignment(101, 1));
    sched.addAssignment(Assignment(102, 2));

    sched.removeAssignment(101);

    EXPECT_EQ(sched.getAssignmentsCount(), 1);
    auto assignments = sched.getAssignments();
    ASSERT_EQ(assignments.size(), 1);
    EXPECT_EQ(assignments[0].getFlightId(), 102);
}

TEST(SchedulerExtendedTest, ClearAllAssignments) {
    Scheduler sched;

    sched.addAssignment(Assignment(101, 1));
    sched.addAssignment(Assignment(102, 2));

    sched.clearAssignments();

    EXPECT_EQ(sched.getAssignmentsCount(), 0);
}
