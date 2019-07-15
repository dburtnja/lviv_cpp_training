//
// Created by denys on 10.07.19.
//

#pragma once


#include "IPerson.hpp"
#include "IRecord.hpp"

class Student : public IPerson, public IRecord {
private:
    int _id;
    std::string _name;


public:
    static const std::string MARKER;

    Student(std::istringstream &istringstream);
    int getId() const override;
    std::string getName() const override;
    std::string getFormatted() const override;
};



