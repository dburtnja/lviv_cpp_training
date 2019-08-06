//
// Created by denys on 10.07.19.
//

#pragma once


#include "AbstractRecord.hpp"

class Exam : public AbstractRecord {
private:
    static const std::string ID;
    static const std::string COURSE_ID;
    static const std::string STUDENT_ID;
    static const std::string RESULT;

    int _id;
    int _course_id;
    int _student_id;
    int _result;

    std::vector<Parameter> _get_print_parameters() const override;

public:

    Exam(std::istringstream &istringstream);
    int getId() const override;
    std::string getFormatted() const override ;
    bool match(const std::vector<Condition> &conditions) const override;
    void update(const std::string &key, const std::string &value) override;
};
