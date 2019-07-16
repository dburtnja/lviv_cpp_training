#include <iostream>
#include <fstream>
#include "RecordsHandler.hpp"
#include "Course.hpp"
#include "Exam.hpp"
#include "Student.hpp"
#include "Teacher.hpp"


int main() {
    RecordsHandler  records_handler;

    try {
        records_handler.read_records("../records.txt");
        records_handler.write_records("../C_records.txt", Course::MARKER);
        records_handler.write_records("../S_records.txt", Student::MARKER);
        records_handler.write_records("../T_records.txt", Teacher::MARKER);
        records_handler.write_records("../E_records.txt", Exam::MARKER);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}