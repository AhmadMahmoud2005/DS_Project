#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Student {
public:
  string id;
  string name;
  string password;
  unordered_set<string> completedCourses;
  unordered_set<string> registeredCourses;
  unordered_map<string, int> grades; // calculate GPA
  Student() {}                       // don't Delete it
  Student(string id, string name, string password) {
    this->id = id;
    this->name = name;
    this->password = password;
  }
  void studentMenu();
  void signUpStudent();
  void loginStudent();
  void searchCourse();
  void RegisterForCourse();
  void viewGrades();
  void showPrerequisites();
  void generateReports();
  void goBack();

  bool checkPrerequisites(string name_or_code);
  double grade_to_gpa_point(int grade);
  double calculate_gpa();
};
