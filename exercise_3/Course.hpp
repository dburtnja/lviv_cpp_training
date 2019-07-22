//
// Created by denys on 10.07.19.
//

#pragma once


#include "ARecord.hpp"

class Course : public ARecord {
private:
    int _id;
    int _teacher_id;
    std::string _name;

    std::list<std::pair<std::string, std::string>> _get_print_parameters() const override;

public:
    static const std::string MARKER;
    static const std::string RECORD_NAME;

    Course(std::istringstream &istringstream);
    int getId() const override;
    std::string getFormatted() const override ;
};



