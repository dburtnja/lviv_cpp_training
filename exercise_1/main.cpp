#include <iostream>
#include "Graph.hpp"

Graph read_from_file(const std::string &file_name) {
    std::ifstream   input_file(file_name);
    if (!input_file) {
        perror("Error on reading file");
        exit(EXIT_FAILURE);
    }
    return Graph(input_file);
}

Graph create_graph(int argc, char **argv) {
    if (argc == 1) {
        return Graph(std::cin);
    } else {
        std::cout << "Reading from file: " << argv[1] << std::endl;
        return read_from_file(argv[1]);
    }
}

void    finding_paths(Graph &graph) {
    std::string buffer;
    std::string start_point_name;
    std::string end_point_name;

    while (true) {
        std::cout << "Please write '<START POINT NAME> <END POINT NAME>' "
                     "for finding shorter path or write 'q' for exit" << std::endl;
        std::getline(std::cin, buffer);
        if ("q" == buffer)
            return;
        std::istringstream  istringstream_buffer(buffer);
        istringstream_buffer >> start_point_name >> end_point_name;
        if (istringstream_buffer.fail()) {
            std::cout << "Invalid input" << std::endl;
            istringstream_buffer.clear();
            istringstream_buffer.ignore(buffer.size());
            continue;
        }
        try {
            graph.calculate_path(start_point_name, end_point_name);
            graph.reset();
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }

    }
}

int main(int argc, char **argv) {
    if (argc > 2) {
        std::cout << "Wrong number arguments" << std::endl;
        return EXIT_FAILURE;
    }
    try {
        Graph graph = create_graph(argc, argv);
        finding_paths(graph);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}