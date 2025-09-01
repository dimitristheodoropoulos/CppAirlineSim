#pragma once

class Assignment {
private:
    int flight_id;
    int crew_id;

public:
    Assignment(int fid, int cid) : flight_id(fid), crew_id(cid) {}
    Assignment() : flight_id(0), crew_id(0) {}

    int getFlightId() const { return flight_id; }
    int getCrewId() const { return crew_id; }
};
