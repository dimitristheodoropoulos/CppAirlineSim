cmake_minimum_required(VERSION 3.10)
project(CPPAirlineSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
    ${PROJECT_SOURCE_DIR}/data/include
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include
)

# Library sources
set(LIB_SOURCES
    src/CSVLoader.cpp
    src/Scheduler.cpp
)

add_library(airline_lib STATIC ${LIB_SOURCES})
target_include_directories(airline_lib PUBLIC ${PROJECT_SOURCE_DIR}/data/include)
target_link_libraries(airline_lib pthread)

# Main executable
add_executable(CPPAirlineSim src/main.cpp)
target_link_libraries(CPPAirlineSim airline_lib pthread)

# Copy data folder
add_custom_command(TARGET CPPAirlineSim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:CPPAirlineSim>/data
)

# Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test sources
set(TEST_SOURCES
    tests/test_scheduler.cpp
    tests/test_scheduler_extended.cpp
    tests/test_scheduler_extended_2.cpp
)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests airline_lib GTest::GTest GTest::Main pthread)
add_test(NAME SchedulerTests COMMAND tests)
