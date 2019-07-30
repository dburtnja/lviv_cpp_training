//
// Created by denys on 10.07.19.
//

#pragma once


#include "AbstractRecord.hpp"

class Exam : public AbstractRecord {
private:
    int _id;
    int _course_id;
    int _student_id;
    int _result;

    std::vector<Parameter> _get_print_parameters() const override;

public:

    Exam(std::istringstream &istringstream);
    int getId() const override;
    std::string getFormatted() const override ;
};



