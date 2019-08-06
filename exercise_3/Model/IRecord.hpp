//
// Created by denys on 10.07.19.
//

#pragma once


#include <string>
#include <functional>
#include <vector>
#include <map>

struct Condition {
    std::string parameter_name;
    std::string compare_sign;
    std::string value;
};

class IRecord {
public:
    virtual int getId() const = 0;
    virtual std::string getFormatted() const = 0;
    virtual std::string getPrettyPrinted() const = 0;
    virtual ~IRecord() = default;

    virtual bool match(const std::vector<Condition> &conditions) const = 0;
    virtual void update(const std::string &key, const std::string &value) = 0;
};
