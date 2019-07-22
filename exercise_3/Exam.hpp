//
// Created by denys on 10.07.19.
//

#pragma once


#include "ARecord.hpp"

class Exam : public ARecord {
private:
    int _id;
    int _course_id;
    int _student_id;
    int _result;

    std::list<std::pair<std::string, std::string>> _get_print_parameters() const override;

public:
    static const std::string MARKER;
    static const std::string RECORD_NAME;

    Exam(std::istringstream &istringstream);
    int getId() const override;
    std::string getFormatted() const override ;
};



