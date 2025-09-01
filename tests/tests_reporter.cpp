#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "=== Running Scheduler Tests with Reporter ===" << std::endl;

    int result = RUN_ALL_TESTS();

    if (result == 0) {
        std::cout << "\nAll tests passed successfully!" << std::endl;
    } else {
        std::cout << "\nSome tests failed. Check details above." << std::endl;
    }

    return result;
}
