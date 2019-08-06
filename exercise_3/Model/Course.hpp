//
// Created by denys on 10.07.19.
//

#pragma once


#include "AbstractRecord.hpp"

class Course : public AbstractRecord {
private:
    static const std::string ID;
    static const std::string NAME;
    static const std::string TEACHER_ID;

    int _id;
    int _teacher_id;
    std::string _name;

    std::vector<Parameter> _get_print_parameters() const override;

public:
    Course(std::istringstream &istringstream);
    int getId() const override;
    std::string getFormatted() const override ;
    bool match(const std::vector<Condition> &conditions) const override;
    void update(const std::string &key, const std::string &value) override;
};



