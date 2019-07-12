#include <iostream>
#include <fstream>
#include "RecordsHandler.hpp"
#include "Course.hpp"
#include "Exam.hpp"
#include "Student.hpp"
#include "Teacher.hpp"

int main() {
    RecordsHandler  records_handler;

    records_handler.add_record_reader<Course>(Course::MARKER);
    records_handler.add_record_reader<Exam>(Exam::MARKER);
    records_handler.add_record_reader<Student>(Student::MARKER);
    records_handler.add_record_reader<Teacher>(Teacher::MARKER);

    if (records_handler.read_records("../records.txt") == EXIT_FAILURE)
        return EXIT_FAILURE;
    records_handler.write_records("../C_records.txt", "C");
    records_handler.write_records("../S_records.txt", "S");
    records_handler.write_records("../T_records.txt", "T");
    records_handler.write_records("../E_records.txt", "E");

    return EXIT_SUCCESS;
}