#include "../headerFiles/Files.h"
#include "../headerFiles/json.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using json = nlohmann::json;

void load_students_from_file(const string &filename,
                             unordered_map<string, Student> &students) {
  ifstream in(filename);
  if (!in.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return;
  }

  json data;
  in >> data;
  in.close();

  if (!data.contains("students"))
    return;

  for (const auto &item : data["students"]) {
    Student s;
    s.id = item["id"];
    s.name = item["name"];
    s.password = item["password"];
    s.completedCourses = item["completed_courses"].get<unordered_set<string>>();
    s.registeredCourses =
        item["registered_courses"].get<unordered_set<string>>();
    s.grades = item["grades"].get<unordered_map<string, int>>();

    students[s.id] = s;
  }
}

void save_students_to_file(const string &filename,
                           const unordered_map<string, Student> &students) {
  json data;

  // Load existing data
  ifstream in(filename);
  if (in.is_open()) {
    in >> data;
    in.close();
  }

  data["students"] = json::array();

  for (unordered_map<string, Student>::const_iterator it = students.begin();
       it != students.end(); ++it) {
    const Student &s = it->second;
    json student_json = {{"id", s.id},
                         {"name", s.name},
                         {"password", s.password},
                         {"completed_courses", s.completedCourses},
                         {"registered_courses", s.registeredCourses},
                         {"grades", s.grades}};
    data["students"].push_back(student_json);
  }

  ofstream out(filename);
  if (!out.is_open()) {
    cerr << "Failed to write to " << filename << endl;
    return;
  }

  out << data.dump(4);
  out.close();
}

void load_admins_from_file(const string &filename,
                           unordered_map<string, Admin> &admins) {
  ifstream in(filename);
  if (!in.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return;
  }

  json data;
  in >> data;
  in.close();

  if (!data.contains("admins"))
    return;

  for (json::const_iterator it = data["admins"].begin();
       it != data["admins"].end(); ++it) {
    const json &item = *it;
    Admin a;
    a.username = item["username"];
    a.password = item["password"];
    admins[a.username] = a;
  }
}

void save_admins_to_file(const string &filename,
                         const unordered_map<string, Admin> &admins) {
  json data;

  ifstream in(filename);
  if (in.is_open()) {
    in >> data;
    in.close();
  }

  data["admins"] = json::array();

  for (unordered_map<string, Admin>::const_iterator it = admins.begin();
       it != admins.end(); ++it) {
    const Admin &a = it->second;
    json admin_json = {{"username", a.username}, {"password", a.password}};
    data["admins"].push_back(admin_json);
  }

  ofstream out(filename);
  if (!out.is_open()) {
    cerr << "Failed to write to " << filename << endl;
    return;
  }

  out << data.dump(4);
  out.close();
}

void loadCoursesFromFile(const string &filename,
                         unordered_map<string, Course> &courses) {
  ifstream in(filename);
  if (!in.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return;
  }

  json data;
  in >> data;
  in.close();

  if (!data.contains("courses"))
    return;

  for (json::const_iterator it = data["courses"].begin();
       it != data["courses"].end(); ++it) {
    const json &course_json = *it;
    Course c;
    c.code = course_json["code"];
    c.name = course_json["name"];
    c.instractor_name = course_json["instractor_name"];
    c.syllabus = course_json["syllabus"];
    c.semester = course_json["semester"];
    c.credit_hours = course_json["credit_hours"];

    for (json::const_iterator p = course_json["prerequisites"].begin();
         p != course_json["prerequisites"].end(); ++p) {
      c.prerequisites.insert(*p);
    }

    courses[c.code] = c;
  }
}

void update_student_grades_from_csv(
    const std::string &csvFile,
    std::unordered_map<std::string, Student> &students) {
  std::ifstream file(csvFile);
  std::string line;

  std::vector<std::string> headers;
  std::unordered_map<std::string, std::unordered_map<std::string, int>>
      csvGrades;

  std::getline(file, line);
  std::stringstream headerStream(line);
  std::string col;
  while (std::getline(headerStream, col, ',')) {
    headers.push_back(col);
  }

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string cell;
    std::string student_id;
    std::unordered_map<std::string, int> grades;

    for (size_t i = 0; i < headers.size(); ++i) {
      std::getline(ss, cell, ',');
      if (i == 0)
        student_id = cell;
      else
        grades[headers[i]] = std::stoi(cell);
    }

    csvGrades[student_id] = grades;
  }

  for (std::unordered_map<std::string,
                          std::unordered_map<std::string, int>>::const_iterator
           it = csvGrades.begin();
       it != csvGrades.end(); ++it) {
    const std::string &id = it->first;
    const std::unordered_map<std::string, int> &grades = it->second;

    if (students.count(id)) {
      for (std::unordered_map<std::string, int>::const_iterator g =
               grades.begin();
           g != grades.end(); ++g) {
        students[id].grades[g->first] = g->second;
      }
    }
  }

  std::cout << "Grades updated from CSV.\n";
}

void save_students_grades_to_csv(
    const std::string &filename,
    const std::unordered_map<std::string, Student> &students) {
  std::ofstream out(filename);
  if (!out.is_open()) {
    std::cerr << "Failed to open file for writing: " << filename << "\n";
    return;
  }

  std::unordered_set<std::string> allCourses;
  for (std::unordered_map<std::string, Student>::const_iterator it =
           students.begin();
       it != students.end(); ++it) {
    for (std::unordered_map<std::string, int>::const_iterator g =
             it->second.grades.begin();
         g != it->second.grades.end(); ++g) {
      allCourses.insert(g->first);
    }
  }

  out << "id";
  for (std::unordered_set<std::string>::const_iterator it = allCourses.begin();
       it != allCourses.end(); ++it) {
    out << "," << *it;
  }
  out << "\n";

  for (std::unordered_map<std::string, Student>::const_iterator it =
           students.begin();
       it != students.end(); ++it) {
    const std::string &id = it->first;
    const Student &student = it->second;
    out << id;
    for (std::unordered_set<std::string>::const_iterator c = allCourses.begin();
         c != allCourses.end(); ++c) {
      std::unordered_map<std::string, int>::const_iterator gradeIt =
          student.grades.find(*c);
      if (gradeIt != student.grades.end()) {
        out << "," << gradeIt->second;
      } else {
        out << ",";
      }
    }
    out << "\n";
  }

  out.close();
  std::cout << "Student grades exported to " << filename << "\n";
}
