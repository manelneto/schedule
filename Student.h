//
// Created by manue on 30/10/2022.
//

#ifndef SCHEDULE_STUDENT_H
#define SCHEDULE_STUDENT_H


#include <vector>
#include "UcClass.h"

class Student {
public:
    Student();
    Student(unsigned code_);
    Student(unsigned code_, const std::string &name_);
    Student(unsigned code_, const std::string &name_, const std::list<UcClass> &ucClasses_);
    unsigned getCode() const;
    std::string getName() const;
    std::list<UcClass> getUcClasses() const;
    void setCode(unsigned code_);
    void setName(const std::string &name_);
    void setUcClasses(const std::list<UcClass> &ucClasses_);
    void addUcClass(const UcClass &ucClass);
    void removeUcClass(const UcClass &ucClass);
    std::vector<bool> getYears() const;
    bool inClass(const UcClass &ucClass) const;
    bool inUc(const UcClass &ucClass) const;
    bool operator<(const Student &other) const;
    void printID() const;
    void print() const;
private:
    unsigned code;
    std::string name;
    std::list<UcClass> ucClasses;
};


#endif //SCHEDULE_STUDENT_H
