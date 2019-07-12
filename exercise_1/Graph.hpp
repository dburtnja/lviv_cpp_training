//
// Created by denys on 08.07.19.
//

#pragma once

#include <list>
#include <fstream>
#include <map>
#include <iostream>
#include <sstream>

template <typename T>
class Graph {
private:
    std::list<T *>           _list_nodes;
    std::map<std::string, T> _map_nodes;

    T                *_create_or_get_node(const std::string &node_name);
    void                _add_nodes(const std::string &name_first, const std::string &name_second, int weight);
    T                *_find_node(const std::string &node_name);
    void                _start_dijkstras_algorithm();
    T                *_find_min_weight_node(std::list<T *> &nodes);
    static void _print_path(T *start_point, T *end_point);

public:
    Graph(std::istream &istream);

    void    calculate_path(const std::string &start_point, const std::string &end_point);
    void    reset();

    template <typename U>
    friend std::ostream &operator<<(std::ostream &stream, const Graph<U> &graph);
};

template<typename T>
Graph<T>::Graph(std::istream &istream) {
    std::string buffer;
    std::string first_node_name;
    std::string second_node_name;
    int         weight;
    int line = 1;

    while (istream) {
        std::getline(istream, buffer);
        if (buffer.empty())
            continue;
        if (buffer == "s")
            break;
        std::istringstream stream_buffer(buffer);
        stream_buffer >> first_node_name >> second_node_name >> weight;
        if (stream_buffer.fail())
            throw std::invalid_argument("Invalid argument in line: " + std::to_string(line));
        this->_add_nodes(first_node_name, second_node_name, weight);
        ++line;
    }
    if (this->_map_nodes.empty())
        throw std::invalid_argument("No path description in file");
    for (auto &value : this->_map_nodes) {
        std:: cout << value.second.get_representation() << std::endl;
        this->_list_nodes.push_back(&(value.second));
    }
    std::cout << "Graph is saved." << std::endl;
}

template<typename T>
T *Graph<T>::_create_or_get_node(const std::string &node_name) {
    auto    iter = this->_map_nodes.find(node_name);

    if (iter != this->_map_nodes.end())
        return &iter->second;
    this->_map_nodes.insert({node_name, T(node_name)});
    return &this->_map_nodes.find(node_name)->second;
}

template<typename T>
void Graph<T>::_add_nodes(const std::string &name_first, const std::string &name_second, int weight) {
    T    *first_node, *second_node;

    first_node = this->_create_or_get_node(name_first);
    second_node = this->_create_or_get_node(name_second);

    first_node->add_connection(second_node, weight);
    second_node->add_connection(first_node, weight);
}

template <typename U>
std::ostream &operator<<(std::ostream &stream, const Graph<U> &graph) {
    for (auto node : graph._list_nodes) {
        stream << *node << std::endl;
    }
    return stream;
}

template<typename T>
T *Graph<T>::_find_node(const std::string &node_name) {
    const auto &iterator = this->_map_nodes.find(node_name);
    if (iterator == this->_map_nodes.end())
        return nullptr;
    return &iterator->second;
}

template <typename T>
void Graph<T>::_print_path(T *start_point, T *end_point) {
    std::list<T *>   result;
    T                *temp;

    temp = end_point;
    result.push_back(temp);
    while (temp != start_point) {
        temp = temp->get_previous();
        result.push_front(temp);
    }
    for (auto node : result) {
        if (node != result.back())
            std::cout << *node << " ->  ";
        else
            std::cout << *node << std::endl;
    }
}

template <typename T>
void    Graph<T>::calculate_path(const std::string &start_point, const std::string &end_point) {
    T    *start_node = this->_find_node(start_point);
    T    *end_node = this->_find_node(end_point);

    if (nullptr == start_node)
        throw std::invalid_argument("No point name: " + start_point);
    if (nullptr == end_node)
        throw std::invalid_argument("No point name: " + end_point);
    if (end_node == start_node)
        throw std::invalid_argument("I can solve harder task.");
    start_node->mark_as_start();
    this->_start_dijkstras_algorithm();
    this->_print_path(start_node, end_node);
}

template <typename T>
void    Graph<T>::_start_dijkstras_algorithm() {
    std::list<T *>   unvisited(this->_list_nodes);
    T    *node;

    while (!unvisited.empty()) {
        node = this->_find_min_weight_node(unvisited);
        node->update_neighbors_weight();
        unvisited.remove(node);
    }
}

template <typename T>
T    *Graph<T>::_find_min_weight_node(std::list<T *> &nodes) {
    T    *tmp;

    tmp = nodes.front();
    for (auto node : nodes) {
        if (node->get_weight() < tmp->get_weight())
            tmp = node;
    }
    return tmp;
}

template <typename T>
void    Graph<T>::reset() {
    for (auto node : this->_list_nodes)
        node->reset();
}

