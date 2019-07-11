//
// Created by denys on 08.07.19.
//

#include <iostream>
#include <sstream>
#include "Graph.hpp"

Graph::Graph(std::istream &istream) {
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

Node *Graph::_create_or_get_node(const std::string &node_name) {
    auto    iter = this->_map_nodes.find(node_name);

    if (iter != this->_map_nodes.end())
        return &iter->second;
//    node = new Node(node_name);
//    this->_map_nodes[node_name] = Node(node_name);
    this->_map_nodes.insert({node_name, Node(node_name)});
    return &this->_map_nodes.find(node_name)->second;
}

void Graph::_add_nodes(const std::string &name_first, const std::string &name_second, int weight) {
    Node    *first_node, *second_node;

    first_node = this->_create_or_get_node(name_first);
    second_node = this->_create_or_get_node(name_second);

    first_node->add_connection(second_node, weight);
    second_node->add_connection(first_node, weight);
}

std::ostream &operator<<(std::ostream &stream, const Graph &graph) {
    for (auto node : graph._list_nodes) {
        stream << *node << std::endl;
    }
    return stream;
}

Node    *Graph::_find_node(const std::string &node_name) {
    std::map<std::string, Node>::iterator iterator;

    iterator = this->_map_nodes.find(node_name);
    if (iterator == this->_map_nodes.end())
        return nullptr;
    return &iterator->second;
}

void Graph::_print_path(Node *start_point, Node *end_point) {
    std::list<Node *>   result;
    Node                *temp;

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

void    Graph::calculate_path(const std::string &start_point, const std::string &end_point) {
    Node    *start_node = this->_find_node(start_point);
    Node    *end_node = this->_find_node(end_point);

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

void    Graph::_start_dijkstras_algorithm() {
    std::list<Node *>   unvisited(this->_list_nodes);
    Node    *node;

    while (!unvisited.empty()) {
        node = this->_find_min_weight_node(unvisited);
        node->update_neighbors_weight();
        unvisited.remove(node);
    }
}

Node    *Graph::_find_min_weight_node(std::list<Node *> &nodes) {
    Node    *tmp;

    tmp = nodes.front();
    for (auto node : nodes) {
        if (node->get_weight() < tmp->get_weight())
            tmp = node;
    }
    return tmp;
}

void    Graph::reset() {
    for (auto node : this->_list_nodes)
        node->reset();
}