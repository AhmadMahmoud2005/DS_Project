#pragma once

#include "globals.h"
using namespace std;

void load_students_from_file(const string &filename,
                             unordered_map<string, Student> &students);
void save_students_to_file(const string &filename,
                           const unordered_map<string, Student> &students);

void load_admins_from_file(const string &filename,
                           unordered_map<string, Admin> &admins);
void save_admins_to_file(const string &filename,
                         const unordered_map<string, Admin> &admins);
void loadCoursesFromFile(const string &filename,
                         unordered_map<string, Course> &courses);
void update_student_grades_from_csv(
    const std::string &csvFile,
    std::unordered_map<std::string, Student> &students);
void save_students_grades_to_csv(
    const std::string &csvFile,
    std::unordered_map<std::string, Student> &students);
