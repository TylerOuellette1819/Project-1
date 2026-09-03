#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

struct Reservation {
    int reservationID;
    int studentID;
    int resourceID;
    std::string date;
    std::string startTime;
    std::string endTime;
};

#endif