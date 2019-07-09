//
// Created by denys on 08.07.19.
//

#pragma once


#include <string>
#include <list>

class Node {
private:
    std::string _node_name;
    std::list<std::pair<Node *, int>> _neighbors;
    int _weight_from_start = std::numeric_limits<int>::max();
    Node    *_previous = nullptr;
    bool    _visited = false;

public:
    Node(std::string node_name);
    Node    *get_previous();
    void    mark_as_start();
    void    update_weight(int weight, Node *updater);
    void    update_neighbors_weight();
    void    add_connection(Node *neighbor, int waight);
    int     get_weight();
    void    reset();

    std::string get_representation();
    friend std::ostream &operator<<(std::ostream &stream, const Node &node);
};


