#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>

class Aircraft {
private:
    int id;
    std::string model;
    int capacity;

public:
    Aircraft(int id_, const std::string& model_)
        : id(id_), model(model_), capacity(0) {}

    Aircraft(int id_, const std::string& model_, int capacity_)
        : id(id_), model(model_), capacity(capacity_) {}

    int getId() const { return id; }
    std::string getModel() const { return model; }
    int getCapacity() const { return capacity; }
};

#endif // AIRCRAFT_H
