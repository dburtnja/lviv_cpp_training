//
// Created by denys on 10.07.19.
//

#pragma once


#include "IRecord.hpp"

class Course : public IRecord {
private:
    int _id;
    int _teacher_id;
    std::string _name;


public:
    Course(std::istringstream &istringstream);
    int getId() const override;
    std::string getFormatted() const override ;
};



