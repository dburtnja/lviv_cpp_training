#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>

//
// Created by denys on 08.07.19.
//

#include "Node.hpp"

Node::Node(std::string node_name) : _node_name(std::move(node_name)) {
}

void Node::add_connection(Node *neighbor, int weight) {
    for (auto pair : this->_neighbors) {
        if (pair.first == neighbor)
            return;
    }
    this->_neighbors.push_back({neighbor, weight});
}

std::ostream &operator<<(std::ostream &stream, const Node &node) {
    stream << node._node_name << "(" << node._weight_from_start << ")";
    return stream;
}

void Node::mark_as_start() {
    this->_weight_from_start = 0;
}

void Node::update_weight(int weight, Node *updater) {
    if (weight < this->_weight_from_start) {
        this->_weight_from_start = weight;
        this->_previous = updater;
    }
}

int Node::get_weight() const {
    return this->_weight_from_start;
}

void    Node::reset() {
    this->_weight_from_start = std::numeric_limits<int>::max();
    this->_previous = nullptr;
    this->_visited = false;
}

void    Node::update_neighbors_weight() {
    for (auto [neighbor, weight] : this->_neighbors) {
        if (!neighbor->_visited) {
            neighbor->update_weight(this->_weight_from_start + weight, this);
        }
    }
    this->_visited = true;
}

Node    *Node::get_previous() const {
    return this->_previous;
}

std::string Node::get_representation() const {
    std::stringstream  stream;
    stream << this->_node_name;
    stream << " (";
    for (auto [neighbor, weight] : this->_neighbors)
        stream << " {" << neighbor->_node_name << ": " << weight << "} ";
    stream << ")";
    return stream.str();
}
