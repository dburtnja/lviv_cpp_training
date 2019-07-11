#include <iostream>
#include <fstream>
#include "RecordsHandler.hpp"


int main() {
    RecordsHandler  records_handler;

    records_handler.read_records("../records.txt");
    records_handler.write_records("../C_records.txt", "C");
    records_handler.write_records("../S_records.txt", "S");
    records_handler.write_records("../T_records.txt", "T");
    records_handler.write_records("../E_records.txt", "E");

    return EXIT_SUCCESS;
}