//
// Created by manue on 30/10/2022.
//

#ifndef SCHEDULE_SLOT_H
#define SCHEDULE_SLOT_H


#include <string>

class Slot {
public:
    Slot();
    Slot(const std::string &weekday_, float startHour, float endHour, const std::string &type_);
    std::string getWeekday() const;
    float getStartHour() const;
    float getEndHour() const;
    std::string getType() const;
    void setWeekday(const std::string &weekday_);
    void setStartHour(float startHour_);
    void setEndHour(float endHour_);
    void setType(const std::string &type_);
    bool overlap(const Slot &other) const;
    bool operator<(const Slot &other) const;
    void print() const;
private:
    std::string weekday;
    float startHour;
    float endHour;
    std::string type;
    unsigned weekdayToNumber() const;
};


#endif //SCHEDULE_SLOT_H
