//
// Created by denys on 08.07.19.
//

#pragma once

#include <list>
#include <fstream>
#include <regex>
#include <map>
#include "Node.hpp"


class Graph {
private:
    std::list<Node *>               _list_nodes;
    std::map<std::string, Node *>   _map_nodes;

    Node                *_create_or_get_node(const std::string &node_name);
    void                _add_nodes(const std::string &name_first, const std::string &name_second, int weight);
    Node                *_get_node(const std::string &node_name);
    void                _start_dijkstras_algorithm();
    Node                *_find_min_weight_node(std::list<Node *> &nodes);
    static void _print_path(Node *start_point, Node *end_point);

public:
    Graph(std::istream &istream);
    ~Graph();

    void    calculate_path(const std::string &start_point, const std::string &end_point);
    void    reset();

    friend std::ostream &operator<<(std::ostream &stream, const Graph &graph);
};



