//
// Created by manue on 30/10/2022.
//

#ifndef SCHEDULE_UCCLASS_H
#define SCHEDULE_UCCLASS_H


#include <list>
#include "Slot.h"

class UcClass {
public:
    UcClass();
    UcClass(const std::string &ucCode_, const std::string &classCode_);
    UcClass(const std::string &ucCode_, const std::string &classCode_, unsigned studentsCount_);
    std::string getUcCode() const;
    std::string getClassCode() const;
    unsigned getStudentsCount() const;
    void setUcCode(const std::string &ucCode_);
    void setClassCode(const std::string &classCode_);
    void setStudentsCount(unsigned studentsCount_);
    void addStudent();
    void removeStudent();
    bool operator<(const UcClass &other) const;
    bool operator==(const UcClass &other) const;
    void print() const;
private:
    std::string ucCode;
    std::string classCode;
    unsigned studentsCount;
};


#endif //SCHEDULE_UCCLASS_H
