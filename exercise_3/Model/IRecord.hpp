//
// Created by denys on 10.07.19.
//

#pragma once


#include <string>

class IRecord {
public:
    virtual int getId() const = 0;
    virtual std::string getFormatted() const = 0;
    virtual std::string getPrettyPrinted() const = 0;
    virtual ~IRecord() = default;
};

