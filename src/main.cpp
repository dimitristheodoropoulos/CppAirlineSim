#include "Flight.h"
#include "Aircraft.h"
#include "Scheduler.h"
#include "CSVLoader.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <unordered_map>

// ANSI colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"

int main() {
    Scheduler scheduler;

    // Load aircrafts
    auto aircrafts = CSVLoader::loadAircraft("data/aircraft.csv");
    if (aircrafts.empty()) { 
        std::cerr << "No aircrafts loaded.\n"; 
        return 1; 
    }

    // Load flights
    auto flights = CSVLoader::loadFlights("data/flights.csv");
    if (flights.empty()) { 
        std::cerr << "No flights loaded.\n"; 
        return 1; 
    }

    // Assign flights to aircrafts (simple round-robin for demo)
    size_t acIndex = 0;
    for (const auto& f : flights) {
        const auto& ac = aircrafts[acIndex % aircrafts.size()];
        scheduler.addAssignment(Assignment(f.getId(), ac.getId()));
        acIndex++;
    }

    // Build flight map
    std::unordered_map<int, const Flight*> flightMap;
    for (const auto& f : flights) flightMap[f.getId()] = &f;

    // Print assignments table with color
    std::cout << "\n=== Flight Assignments ===\n";
    std::cout << std::left 
              << std::setw(8) << "FlightID"
              << std::setw(12) << "AircraftID"
              << std::setw(14) << "FlightNum"
              << std::setw(14) << "Airline"
              << std::setw(10) << "DepTime"
              << std::setw(10) << "ArrTime"
              << std::setw(6)  << "From"
              << std::setw(6)  << "To" << "\n";
    std::cout << std::string(90, '-') << "\n";

    for (const auto& a : scheduler.getAssignments()) {
        auto it = flightMap.find(a.getFlightId());
        if (it == flightMap.end()) continue;
        const Flight* flight = it->second;

        int depMins = Scheduler::timeToMinutes(flight->getDepartureTime());
        int arrMins = Scheduler::timeToMinutes(flight->getArrivalTime());

        std::string color = GREEN;
        for (const auto& other : scheduler.getAssignments()) {
            if (other.getCrewId() == a.getCrewId() && other.getFlightId() != a.getFlightId()) {
                auto itOther = flightMap.find(other.getFlightId());
                if (itOther == flightMap.end()) continue;

                int otherDep = Scheduler::timeToMinutes(itOther->second->getDepartureTime());
                int otherArr = Scheduler::timeToMinutes(itOther->second->getArrivalTime());

                if ((depMins < otherArr) && (arrMins > otherDep)) { 
                    color = RED; 
                    break; 
                }
                if ((depMins - otherArr) > 0 && (depMins - otherArr) < 30) { 
                    color = YELLOW; 
                }
            }
        }

        std::cout << color
                  << std::left
                  << std::setw(8)  << a.getFlightId()
                  << std::setw(12) << a.getCrewId()
                  << std::setw(14) << flight->getFlightNumber()
                  << std::setw(14) << flight->getAirline()
                  << std::setw(10) << flight->getDepartureTime()
                  << std::setw(10) << flight->getArrivalTime()
                  << std::setw(6)  << flight->getOrigin()
                  << std::setw(6)  << flight->getDestination()
                  << RESET << "\n";
    }

    // Estimated memory usage
    size_t memFlights = flights.size() * sizeof(Flight);
    size_t memAircrafts = aircrafts.size() * sizeof(Aircraft);
    size_t memAssignments = scheduler.getAssignmentsCount() * sizeof(Assignment);

    std::cout << "\nEstimated memory usage:\n";
    std::cout << "Flights: " << memFlights / 1024.0 << " KB\n";
    std::cout << "Aircraft: " << memAircrafts / 1024.0 << " KB\n";
    std::cout << "Assignments: " << memAssignments / 1024.0 << " KB\n";

    return 0;
}
