//
// Created by denys on 10.07.19.
//

#pragma once


#include "IRecord.hpp"

class Exam : public IRecord {
private:
    int _id;
    int _course_id;
    int _student_id;
    int _result;


public:
    static const std::string MARKER;

    Exam(std::istringstream &istringstream);
    int getId() const override;
    std::string getFormatted() const override ;
};



