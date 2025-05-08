#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Admin {
public:
  string username;
  string password;
  Admin();
  Admin(string username, string password);
  void signUpAdmin();
  void loginAdmin();
  void addCourse(string code, string name, string instractor_name,
                 string syllabus, float credit_hours);
  void setPrerequisites(string code, unordered_set<string> prerequistes);
};
