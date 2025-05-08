#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "Admin.h"
#include "Course.h"
#include "Student.h"
#include <string>
#include <unordered_map>

extern unordered_map<string, Admin> admins;
extern unordered_map<string, Student> students;
extern unordered_map<string, Course> courses;
extern void mainMenu();

#endif
