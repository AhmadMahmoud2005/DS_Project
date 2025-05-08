#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Course {
public:
  string code;
  string name;
  string instractor_name;
  string syllabus;
  string semester;
  float credit_hours;
  unordered_set<string> prerequisites;
  Course();
};
