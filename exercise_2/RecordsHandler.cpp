//
// Created by denys on 10.07.19.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "RecordsHandler.hpp"


int RecordsHandler::read_records(const std::string &file_name) {
    std::ifstream   file(file_name);
    std::string     buffer;

    if (!file) {
        perror("Can't open file");
        return EXIT_FAILURE;
    }
    while (file) {
        std::getline(file, buffer);
        if (!buffer.empty())
            this->_add_record(buffer);
    }
    return EXIT_SUCCESS;
}

void RecordsHandler::_add_record(const std::string &record) {
    std::istringstream  istringstream_record(record);
    std::string         record_type_marker;


    if (!std::getline(istringstream_record, record_type_marker, ','))
        exit(EXIT_FAILURE);
    if (auto object_creator = this->_get_record_creator(record_type_marker)) {
        auto object = object_creator(istringstream_record);
        this->_store_in_record_container(record_type_marker, object);
    }
}

RecordsHandler::_object_creator_type RecordsHandler::_get_record_creator(const std::string &record_marker) const {
    auto object_creator_iterator = _OBJECT_CREATORS.find(record_marker);
    if (object_creator_iterator == _OBJECT_CREATORS.end())
        return nullptr;
    return object_creator_iterator->second;
}

std::map<int, std::shared_ptr<IRecord>> &RecordsHandler::_get_records(const std::string &records_marker) {
    auto container_iterator = CONTAINERS.find(records_marker);
    if (container_iterator == CONTAINERS.end())
        throw std::invalid_argument("CONTAINERS map don't have " + records_marker + " key.");
    return container_iterator->second;
}

void RecordsHandler::_store_in_record_container(const std::string &record_marker, const std::shared_ptr<IRecord>& record) {
    auto &container = this->_get_records(record_marker);
    container[record->getId()] = record;
}

void RecordsHandler::print_records(const std::string &records_marker) {
    std::cout << "Print records" << std::endl;
    std::cout <<  this->_get_records(records_marker).size() << std::endl;

    for (auto [id, record] : this->_get_records(records_marker)) {
        auto a = record->getFormatted();
        std::cout << id << " " << record->getFormatted() << std::endl;
    }
}

void RecordsHandler::print_records(const std::string &records_marker, std::ofstream &ofstream) {
    std::cout << "Printing to file:";
    std::cout <<  this->_get_records(records_marker).size() << records_marker << std::endl;

    for (const auto &record_iterator : this->_get_records(records_marker))
        ofstream << records_marker << ',' << record_iterator.second->getFormatted() << std::endl;
}

int RecordsHandler::write_records(const std::string &file_name, const std::string &records_marker) {
    std::ofstream   file(file_name);
    std::string     buffer;

    if (!file) {
        perror("Can't write to file");
        return EXIT_FAILURE;
    }
    try {
        this->print_records(records_marker, file);
    } catch (std::exception &e) {
        std::cerr << "No records with marker: " << records_marker << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
