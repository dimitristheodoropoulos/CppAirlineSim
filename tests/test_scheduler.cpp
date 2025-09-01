#include "../data/include/Scheduler.h"
#include "../data/include/Assignment.h"
#include <gtest/gtest.h>

TEST(SchedulerTest, AddAndCountAssignments) {
    Scheduler sched;
    Assignment a1(101, 1);
    Assignment a2(102, 2);

    sched.addAssignment(a1);
    sched.addAssignment(a2);

    EXPECT_EQ(sched.getAssignmentsCount(), 2);
}

TEST(SchedulerTest, RemoveAssignment) {
    Scheduler sched;
    Assignment a1(101, 1);
    sched.addAssignment(a1);

    sched.removeAssignment(101);
    EXPECT_EQ(sched.getAssignmentsCount(), 0);
}

TEST(SchedulerTest, ClearAssignments) {
    Scheduler sched;
    sched.addAssignment(Assignment(101, 1));
    sched.addAssignment(Assignment(102, 2));

    sched.clearAssignments();
    EXPECT_EQ(sched.getAssignmentsCount(), 0);
}
