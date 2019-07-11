//
// Created by denys on 10.07.19.
//

#pragma once


#include <map>
#include <memory>
#include "Course.hpp"
#include "Exam.hpp"
#include "Student.hpp"
#include "Teacher.hpp"


class RecordsHandler {
private:
    template <typename T>
    static std::shared_ptr<IRecord> _constructor(std::istringstream &istringstream) {
        return std::make_shared<T>(istringstream);
    }
    using _constructor_type = std::shared_ptr<IRecord> (*)(std::istringstream &);
    std::map<std::string, _constructor_type>  CONSTRUCTORS;
    std::map<std::string, std::map<int, std::shared_ptr<IRecord>>> CONTAINERS;

    template <typename RecordClass>
    void _add_record_type(const std::string &record_marker) {
        CONSTRUCTORS[record_marker] = &(RecordsHandler::_constructor<RecordClass>);
        CONTAINERS[record_marker] = std::map<int, std::shared_ptr<IRecord>>{};
    }

    _constructor_type _get_record_constructor(const std::string &record_marker) const;
    void _store_in_record_container(const std::string &record_marker, const std::shared_ptr<IRecord>& record);


    void _add_record(const std::string &record);
    std::map<int, std::shared_ptr<IRecord>> &_get_records(const std::string &records_marker);

public:
    RecordsHandler();
    int read_records(const std::string &file_name);
    int write_records(const std::string &file_name, const std::string &records_marker);
    void print_records(const std::string &records_marker);
    void print_records(const std::string &records_marker, std::ofstream &ofstream);
};
