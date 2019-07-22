//
// Created by denys on 10.07.19.
//

#pragma once


#include <map>
#include <list>
#include <memory>
#include <functional>
#include "IRecord.hpp"
#include "ICommand.hpp"


class RecordsHandler {
private:
    static const std::list<std::pair<std::string, std::string>> RECORD_MARKERS;
    std::map<std::string, std::map<int, std::shared_ptr<IRecord>>> CONTAINERS;

    void _store_in_record_container(const std::string &record_marker, const std::shared_ptr<IRecord>& record);
    void _add_record(const std::string &record);
    const std::map<int, std::shared_ptr<IRecord>> &_get_records_by_marker(const std::string &records_marker) const;

public:
    RecordsHandler() = default;
    explicit RecordsHandler(const std::string &file_name);
    void read_records(const std::string &file_name);
    void dump_records(std::ostream &ostream, const std::string &table_name);
    const std::map<int, std::shared_ptr<IRecord>> &get_records(const std::string &table_name) const;
    std::list<std::string> get_tables() const;
};
