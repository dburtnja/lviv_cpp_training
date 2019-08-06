//
// Created by denys on 10.07.19.
//

#pragma once


#include <vector>
#include <map>
#include "IPerson.hpp"
#include "AbstractRecord.hpp"

class Student : public IPerson, public AbstractRecord {
private:
    static const std::string ID;
    static const std::string NAME;

    int _id;
    std::string _name;
    std::vector<Parameter> _get_print_parameters() const override;

public:

    Student(std::istringstream &istringstream);
    int getId() const override;
    std::string getName() const override;
    std::string getFormatted() const override;
    bool match(const std::vector<Condition> &conditions) const override;
    void update(const std::string &key, const std::string &value) override;
};
