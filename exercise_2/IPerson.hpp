//
// Created by denys on 10.07.19.
//

#pragma once


#include <string>
#include "IRecord.hpp"

class IPerson : public IRecord {
public:
    virtual std::string getName() const = 0;
    virtual ~IPerson() = default;
};



