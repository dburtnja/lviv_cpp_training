//
// Created by denys on 10.07.19.
//

#pragma once


#include <map>
#include <list>
#include <memory>
#include <functional>
#include "IRecord.hpp"
#include "Table.hpp"


class RecordsHandler {
private:
    std::map<std::string, Table> _tables;

    void _init_tables();
    void _add_record(const std::string &record);

public:
    RecordsHandler() = default;
    explicit RecordsHandler(const std::string &file_name);

    void read_records(const std::string &file_name);
    void dump_records(std::ostream &ostream, const std::string &table_name);
    void dump_records(std::ostream &ostream);
    const std::map<int, std::shared_ptr<IRecord>> &get_records(const std::string &table_name) const;
    const Table &get_table(const std::string &table_name) const;
    const Table &get_table_by_marker(const std::string &table_marker) const;
    std::vector<std::string> get_tables() const;
};
