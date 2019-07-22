//
// Created by denys on 20.07.19.
//

#pragma once


#include "IRecord.hpp"
#include <list>

class ARecord : public IRecord {
private:
    virtual std::list<std::pair<std::string, std::string>> _get_print_parameters() const = 0;

public:
    std::string getPrettyPrinted() const override ;
};



