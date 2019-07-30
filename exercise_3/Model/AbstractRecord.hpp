//
// Created by denys on 20.07.19.
//

#pragma once


#include "IRecord.hpp"
#include <vector>

struct Parameter {
    std::string first;
    std::string second;
};

class AbstractRecord : public IRecord {
private:
    virtual std::vector<Parameter> _get_print_parameters() const = 0;

public:
    std::string getPrettyPrinted() const override ;
};
