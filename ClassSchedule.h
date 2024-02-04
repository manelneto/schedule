//
// Created by manue on 30/10/2022.
//

#ifndef SCHEDULE_CLASSSCHEDULE_H
#define SCHEDULE_CLASSSCHEDULE_H


#include "UcClass.h"

class ClassSchedule {
public:
    ClassSchedule();
    ClassSchedule(const UcClass &ucClass_);
    ClassSchedule(const UcClass &ucClass_, const std::list<Slot> &slots_);
    UcClass getUcClass() const;
    std::list<Slot> getSlots() const;
    void setUcClass(const UcClass &ucClass_);
    void setSlots(const std::list<Slot> &slots_);
    void addSlot(const Slot &slot);
    bool overlap(const Slot &other) const;
    bool operator==(const ClassSchedule &other) const;
    void print() const;
private:
    UcClass ucClass;
    std::list<Slot> slots;
};


#endif //SCHEDULE_CLASSSCHEDULE_H
