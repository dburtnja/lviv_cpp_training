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

protected:
    bool match_parameters(const std::vector<Condition> &conditions, std::map<std::string, std::string> parameters) const;
    bool match_parameters(const std::vector<Condition> &conditions, std::map<std::string, int> parameters) const;
    template <typename T>
    static bool compare(T first, const std::string &compare_sign, T second);
    int str_to_int(const std::string &input);

public:
    std::string getPrettyPrinted() const override ;
};

template<typename T>
bool AbstractRecord::compare(T first, const std::string &compare_sign, T second) {
    if ("=" == compare_sign)
        return first == second;
    if (">" == compare_sign)
        return first > second;
    if ("<" == compare_sign)
        return first < second;
    if (">=" == compare_sign)
        return first >= second;
    if ("<=" == compare_sign)
        return first <= second;
    throw std::invalid_argument("Unexpected compare sign: '" + compare_sign + "'.");
}
