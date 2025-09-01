#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

class Flight {
public:
    int id;
    std::string flightNumber;
    std::string departure;
    std::string arrival;
    std::string airline;

    Flight(int id_, const std::string& flightNumber_, const std::string& dep,
           const std::string& arr, const std::string& airline_)
        : id(id_), flightNumber(flightNumber_), departure(dep), arrival(arr), airline(airline_) {}

    // getters
    int getId() const { return id; }
    std::string getFlightNumber() const { return flightNumber; }
    std::string getDepartureTime() const { return departure; }
    std::string getArrivalTime() const { return arrival; }
    std::string getOrigin() const { return departure; }
    std::string getDestination() const { return arrival; }
    std::string getAirline() const { return airline; }

    Flight(const Flight&) = default;
    Flight(Flight&&) = default;
};

#endif // FLIGHT_H
