# C++ Airline Simulator

## Overview
This project is a **C++ Airline Scheduling and Flight Assignment Simulator**.  
It demonstrates:

- Loading aircraft and flight data from CSV files.
- Assigning flights to aircraft using a simple scheduling algorithm.
- Checking for overlapping schedules and highlighting conflicts.
- Estimating memory usage for flights, aircraft, and assignments.
- Unit testing with GoogleTest to ensure correct scheduler behavior.

The project is intended as a **showcase for C++ development, algorithm design, and software engineering skills**, suitable for demonstrating practical skills to potential employers.

---

## Features

1. **Flight and Aircraft Management**
   - Load flights and aircraft from CSV files.
   - Store data in well-structured classes (`Flight`, `Aircraft`, `Assignment`).
   - Maintain flight assignments with conflict detection.

2. **Scheduler**
   - Simple round-robin flight assignment.
   - Conflict detection (overlapping schedules for the same aircraft).
   - Output a color-coded table indicating schedule status:
     - Green: No conflict
     - Yellow: Minor overlap (<30 minutes)
     - Red: Conflict

3. **CSV Loader**
   - Load structured flight and aircraft data from CSV files.
   - Easy extension to load crew data and other resources.

4. **Testing**
   - GoogleTest unit tests for the Scheduler.
   - Covers add/remove/clear assignments, concurrent operations.

5. **Memory Estimation**
   - Quick insight into memory usage for flights, aircraft, and assignments.

---

## Usage

1. Build the project:
```bash
mkdir build
cd build
cmake ..
make -j4


Run the main simulation:
./CPPAirlineSim


Run the unit tests:
./tests


CSV File Format

Aircraft (aircraft.csv)
id,model,capacity
1,Boeing737,180
2,AirbusA320,160
...

Flights (flights.csv)
id,origin,destination,depTime,duration
1,LHR,DXB,12:23,420
2,DXB,SIN,09:03,360
...

Crew (crew.csv) (currently empty, future extension)
id,name,role

Potential Extensions and Optimizations
1. Algorithmic Enhancements

Flight Assignment

Current: simple round-robin.

Future: implement Greedy, Backtracking, or Constraint Satisfaction algorithms for optimized scheduling.

For searching and sorting operations (e.g., finding the next available aircraft or overlapping flights):

Use binary search or hash maps for fast lookup.

Sort flights by departure time using std::sort (O(n log n)) for scheduling efficiency.

Conflict Detection

Current: linear scan of all assignments.

Future: interval trees or segment trees for O(log n) conflict queries.

2. Large-scale Deployment

Introduce a database backend (e.g., PostgreSQL, MongoDB) for storing flights and aircraft.

Enable multi-user access with a REST API interface.

Use caching for frequently queried schedules to improve performance.

3. Parallelism / Multithreading

Currently single-threaded; large datasets may slow down assignments and conflict checking.

Future: use C++ threads or OpenMP for:

Concurrent flight assignment.

Parallel conflict detection.

Faster CSV parsing.

Multithreaded scheduler can significantly reduce runtime when scaling to thousands of flights and aircraft.

4. Other Enhancements

Crew assignment with availability constraints.

Graphical visualization of schedules (e.g., Gantt charts using a GUI or web frontend).

Export schedule to Excel/CSV for reporting purposes.

Integration with real-world airline data for demonstration in interviews or showcases.

Showcase Goal

This project is designed to be both a working local simulation and a showcase project for potential employers.
It highlights:

Strong understanding of C++ OOP principles.

Practical algorithm implementation for scheduling and conflict detection.

Familiarity with unit testing and build systems (CMake).

Ability to think about scalability and parallel programming.
