//
// Created by manue on 30/10/2022.
//

#ifndef SCHEDULE_REQUEST_H
#define SCHEDULE_REQUEST_H


#include "Student.h"

class Request {
public:
    Request();
    Request(const Student &student_, const UcClass &origin_, UcClass const &destination_, unsigned type_);
    Student getStudent() const;
    UcClass getOrigin() const;
    UcClass getDestination() const;
    unsigned getType() const;
    void setStudent(const Student &student_);
    void setOrigin(const UcClass &origin_);
    void setDestination(const UcClass &destination_);
    void setType(unsigned type_);
    void print() const;
private:
    Student student;
    UcClass origin;
    UcClass destination;
    unsigned type;
};


#endif //SCHEDULE_REQUEST_H
