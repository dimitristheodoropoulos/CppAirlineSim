#pragma once
#include <string>
#include <vector>
#include "Flight.h"
#include "Aircraft.h"
#include "Crew.h"

class CSVLoader {
public:
    static std::vector<Flight> loadFlights(const std::string& filename);
    static std::vector<Aircraft> loadAircraft(const std::string& filename);
    static std::vector<Crew> loadCrew(const std::string& filename); // νέο
};
