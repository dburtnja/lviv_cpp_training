//
// Created by denys on 10.07.19.
//

#pragma once


#include <map>
#include <memory>
#include "IRecord.hpp"


class RecordsHandler {
private:
    std::map<std::string, std::map<int, std::shared_ptr<IRecord>>> CONTAINERS;

    void _store_in_record_container(const std::string &record_marker, const std::shared_ptr<IRecord>& record);
    static std::shared_ptr<IRecord> _create(const std::string &type_marker, std::istringstream &istringstream_record);
    void _add_record(const std::string &record);
    std::map<int, std::shared_ptr<IRecord>> &_get_records(const std::string &records_marker);

public:
    RecordsHandler() = default;
    void read_records(const std::string &file_name);
    void write_records(const std::string &file_name, const std::string &records_marker);
    void print_records(const std::string &records_marker);
    void print_records(const std::string &records_marker, std::ofstream &ofstream);
};
