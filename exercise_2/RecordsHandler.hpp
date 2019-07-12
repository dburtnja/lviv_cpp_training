//
// Created by denys on 10.07.19.
//

#pragma once


#include <map>
#include <memory>
#include "IRecord.hpp"


class RecordsHandler {
private:
    template <typename T>
    static std::shared_ptr<IRecord> _object_creator(std::istringstream &istringstream) {
        return std::make_shared<T>(istringstream);
    }
    using _object_creator_type = std::shared_ptr<IRecord> (*)(std::istringstream &);
    std::map<std::string, _object_creator_type>  _OBJECT_CREATORS;
    std::map<std::string, std::map<int, std::shared_ptr<IRecord>>> CONTAINERS;

    template <typename RecordClass>
    void _add_record_type(const std::string &record_marker) {
        _OBJECT_CREATORS[record_marker] = &(RecordsHandler::_object_creator<RecordClass>);
        CONTAINERS[record_marker] = {};
    }

    _object_creator_type _get_record_creator(const std::string &record_marker) const;
    void _store_in_record_container(const std::string &record_marker, const std::shared_ptr<IRecord>& record);


    void _add_record(const std::string &record);
    std::map<int, std::shared_ptr<IRecord>> &_get_records(const std::string &records_marker);

public:
    RecordsHandler() = default;
    int read_records(const std::string &file_name);
    int write_records(const std::string &file_name, const std::string &records_marker);
    void print_records(const std::string &records_marker);
    void print_records(const std::string &records_marker, std::ofstream &ofstream);

    template <typename RecordClass>
    int add_record_reader(const std::string &record_marker);
};

template<typename RecordClass>
int RecordsHandler::add_record_reader(const std::string &record_marker) {
    if (_OBJECT_CREATORS.find(record_marker) != _OBJECT_CREATORS.end())
        return EXIT_FAILURE;
    this->_add_record_type<RecordClass>(record_marker);
    return EXIT_SUCCESS;
}
