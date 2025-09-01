#ifndef CREW_H
#define CREW_H

#include <string>

class Crew {
public:
    int id;
    std::string name;
    std::string role; // νέο πεδίο

    // Constructor που ταιριάζει με CSVLoader
    Crew(int id_, const std::string& name_, const std::string& role_)
        : id(id_), name(name_), role(role_) {}

    Crew(const Crew&) = default;
    Crew(Crew&&) = default;
};

#endif // CREW_H
