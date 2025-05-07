#include "json.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <termios.h>
#include <conio.h>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using json = nlohmann::json;

void mainMenu();

class Course {
public:
  string code;
  string name;
  string instractor_name;
  string syllabus;
  string semester;
  float credit_hours;
  unordered_set<string> prerequisites;
  Course() {

    this->code = "";
    this->name = "";
    this->instractor_name = "";
    this->syllabus = "";
    this->credit_hours = 0.0;
    this->semester = "";
  }
  /*Course(string id, string name, vector<string>prerequisites) {
          this->code = id;
          this->name = name;
          this->prerequisites = prerequisites;
  }*/
};
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
class Admin {
public:
  string username;
  string password;
  Admin() {} // don't Delete it
  Admin(string username, string password) {
    this->username = username;
    this->password = password;
  }
  void signUpAdmin();
  void loginAdmin();
  void addCourse(string code, string name, string instractor_name,
                 string syllabus, float credit_hours);
  void setPrerequisites(string code, unordered_set<string> prerequistes);
};

// Data
unordered_map<string, Student> students;
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

  // Load existing admins (so we don't overwrite them)
  ifstream in(filename);
  if (in.is_open()) {
    in >> data;
    in.close();
  }

  data["students"] = json::array();

  for (const auto &[id, s] : students) {
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

  out << data.dump(4); // pretty print
  out.close();
}

unordered_map<string, Admin> admins;
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

  for (const auto &item : data["admins"]) {
    Admin a;
    a.username = item["username"];
    a.password = item["password"];
    admins[a.username] = a;
  }
}
void save_admins_to_file(const string &filename,
                         const unordered_map<string, Admin> &admins) {
  json data;

  // Preserve existing students
  ifstream in(filename);
  if (in.is_open()) {
    in >> data;
    in.close();
  }

  data["admins"] = json::array();

  for (const auto &[username, a] : admins) {
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

unordered_map<string, Course> courses;
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

  for (const auto &course_json : data["courses"]) {
    Course c;
    c.code = course_json["code"];
    c.name = course_json["name"];
    c.instractor_name = course_json["instractor_name"];
    c.syllabus = course_json["syllabus"];
    c.semester = course_json["semester"];
    c.credit_hours = course_json["credit_hours"];

    for (const auto &prereq : course_json["prerequisites"]) {
      c.prerequisites.insert(prereq);
    }

    courses[c.code] = c;
  }
}

void Student::studentMenu() {
  cout << "Hello, " << this->name << "\n";
  cout << "Your Courses:\n";
  for (const auto &course : registeredCourses) {
    cout << course << "  ";
  }
  cout << "\n";

  int choice = -1;
  cout << "1. Search for Courses\n2. Register Course\n3. View Grades\n4. Check "
          "Prerequisites\n5. Generate Report\n0. Logout\n";
  cout << "Enter your choice: ";
  cin >> choice;
  switch (choice) {
  case 1:
    searchCourse();
    break;
  case 2:
    RegisterForCourse();
    break;
  case 3:
    viewGrades();
    break;
  case 4:
    showPrerequisites();
    break;
  case 5:
    generateReports();
    break;
  case 0:
    mainMenu();
    break;
  default:
    break;
  }
}
void Student::signUpStudent() {
  string id, name, password;
  cout << "enter Student ID: ";
  cin >> id;
  if (students.find(id) !=
      students.end()) // if exists a Student has this ID in H.Table
  {
    cout << "Student already exists.\n";
    return;
  }
  cout << "enter Student Name: ";
  cin.ignore();
  getline(cin, name);
  cout << "enter Student Password: ";
  cin >> password;
  Student student(id, name, password);
  students[id] = student;
  cout << "SignUp successfully\n";
  student.studentMenu();
}
void Student::loginStudent() {
  string id, password;
  int input = 0;
  while (input < 3) {
    cout << "enter Student ID: ";
    cin >> id;
    cout << "enter Student password: ";
    password = "";
    char ch;
    while ((ch = _getch()) != '\n') { // use '\n' for Enter on Linux
      if (ch == 127 || ch == '\b') { // handle Backspace (127 on Linux)
        if (!password.empty()) {
          password.pop_back();
          cout << "\b \b";
        }
      } else {
        password += ch;
        cout << '*';
      }
      cout.flush(); // ensure output appears immediately
    }
    cout << endl;
    if (students.find(id) ==
        students.end()) // if doesn't exist a Student has this ID in H.Table
    {
      cout << "the Student doesn't exist.\n";
      return;
    } else {
      auto it = students.find(id);
      if (it->second.password != password) {
        cout << "wrong Password \n";
        input++;
        if (input == 3) {
          cout << "your tried three wrong Passwords\n";
          return;
        }
        continue;
      } else {
        cout << "Login Student successfully\n";
        it->second.studentMenu();
        return;
      }
    }
  }
}
void Student::goBack() {
  cout << "Enter anything to back\n";
  char choice;
  cin >> choice;
  if (choice)
    this->studentMenu();
}
void Student::searchCourse() {
  cout << "Availabe Courses Are:" << endl;
  for (auto it = courses.begin(); it != courses.end(); it++) {
    cout << "Code: " << it->first << "\t" << "name: " << it->second.name
         << endl;
  }
  goBack();
}
void Student::RegisterForCourse() {
  string code;
  cout << "Enter course code: ";
  cin >> code;
  bool checkprerequisites = checkPrerequisites(code);
  if (checkprerequisites)
    this->registeredCourses.insert(code);
  else
    cout << "You can't be registered to this course you have to complete "
            "prerequisites first!"
         << endl;
  goBack();
}
bool Student::checkPrerequisites(string code) {

  int completedCoursesSize = this->completedCourses.size();
  int prerequisitesSize = courses[code].prerequisites.size();
  if (prerequisitesSize == 0)
    return true;
  else {
    if (completedCoursesSize == 0)
      return false;
    else {
      if (prerequisitesSize > completedCoursesSize)
        return false;
      else {
        unordered_set<string>::iterator completedCoursesIt;
        unordered_set<string>::iterator prerequisitesIt;

        for (prerequisitesIt = courses[code].prerequisites.begin();
             prerequisitesIt != courses[code].prerequisites.end();
             prerequisitesIt++) {
          completedCoursesIt = this->completedCourses.find(*prerequisitesIt);
          if (completedCoursesIt == this->completedCourses.end())
            return false;
        }
        return true;
      }
    }
  }
}
void Student::viewGrades() {
  cout << "Your Grades:\n";
  for (const auto &grade : grades) {
    auto &course = courses[grade.first];
    cout << course.name << " -> (Grades: " << grade.second << ") ("
         << course.semester << ")\n";
  }
  goBack();
}
double Student::grade_to_gpa_point(int grade) {
  if (grade >= 90)
    return 4.0;
  if (grade >= 85)
    return 3.5;
  if (grade >= 80)
    return 3.0;
  if (grade >= 75)
    return 2.5;
  if (grade >= 70)
    return 2.0;
  if (grade >= 65)
    return 1.5;
  if (grade >= 60)
    return 1.0;
  return 0.0;
}
double Student::calculate_gpa() {
  if (grades.empty())
    return 0.0;

  double total_weighted_points = 0.0;
  double total_credits = 0.0;

  for (const auto &grade : grades) {
    auto it = courses.find(grade.first);
    if (it == courses.end())
      continue;

    double credit = it->second.credit_hours;
    double gpa_point = grade_to_gpa_point(grade.second);
    total_weighted_points += gpa_point * credit;
    total_credits += credit;
  }

  return (total_credits == 0) ? 0.0 : (total_weighted_points / total_credits);
}
void Student::generateReports() {
  cout << "Name: " << name << "\n";
  cout << "ID: " << id << "\n";

  cout << "Courses taken: \n";
  for (const auto &course : completedCourses)
    cout << course << ": " << grades[course] << "(" << courses[course].semester
         << ")\n";
  cout << "GPA: " << calculate_gpa() << "\n";
  goBack();
}
void Student::showPrerequisites() {
  cout << "|\tCourse\t||\tPrerequisties\t|\n";
  for (const auto &course : courses) {
    cout << "| " << course.second.name << " ||";
    for (const auto &pre : course.second.prerequisites)
      cout << " " << pre;
    cout << "\n";
  }
  goBack();
}
void Admin::signUpAdmin() {
  string username, password;
  cout << "Enter Admin Username: ";
  cin >> username;

  if (admins.find(username) != admins.end()) {
    cout << "Admin already exists.\n";
    return;
  }

  cout << "Enter Password: ";
  cin >> password;
  Admin admin(username, password);
  admins[username] = admin;
  cout << "Admin registered successfully.\n";
}
void Admin::loginAdmin() {
  string username, password;
  int input = 0;
  while (input < 3) {
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    password = "";
    char ch;
    while ((ch = _getch()) != '\n') { // use '\n' for Enter on Linux
      if (ch == 127 || ch == '\b') { // handle Backspace (127 on Linux)
        if (!password.empty()) {
          password.pop_back();
          cout << "\b \b";
        }
      } else {
        password += ch;
        cout << '*';
      }
      cout.flush(); // ensure output appears immediately
    }
    cout << endl;

    if (admins.find(username) == admins.end()) {
      cout << "Admin doesn't exists.\n";
      return;
    } else {
      auto it = admins.find(username);
      if (it->second.password != password) {
        cout << "wrong Password \n";
        input++;
        if (input == 3) {
          cout << "your tried three wrong Passwords\n";
          return;
        }
        continue;
      } else {
        cout << "Login Admin successfully\n";
        return;
      }
    }
  }
}
void Admin::addCourse(string code, string name, string instractor_name,
                      string syllabus, float credit_hours) {
  Course course;
  course.code = code;
  course.credit_hours = credit_hours;
  course.name = name;
  course.instractor_name = instractor_name;
  course.syllabus = syllabus;

  courses.insert(make_pair(code, course));
}
void Admin::setPrerequisites(string code, unordered_set<string> prerequisites) {
  courses[code].prerequisites = prerequisites;
}

// Adjust to match Student class
void update_student_grades_from_csv(
    const std::string &csvFile,
    std::unordered_map<std::string, Student> &students) {
   std::ifstream file(csvFile);
   std::string line;

   std::vector<std::string> headers;
   std::unordered_map<std::string, std::unordered_map<std::string, int>>
       csvGrades;

   // Parse headers
   std::getline(file, line);
   std::stringstream headerStream(line);
   std::string col;
   while (std::getline(headerStream, col, ',')) {
      headers.push_back(col);
   }

   // Parse CSV data
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

   // Update students map
   for (const auto &[id, grades] : csvGrades) {
      if (students.count(id)) {
         for (const auto &[course, grade] : grades) {
            students[id].grades[course] = grade;
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

   // 1. Collect all course codes that appear in any student's grades
   std::unordered_set<std::string> allCourses;
   for (const auto &[id, student] : students) {
      for (const auto &[course, _] : student.grades) {
         allCourses.insert(course);
      }
   }

   // 2. Write header row: id,course1,course2,...
   out << "id";
   for (const auto &course : allCourses) {
      out << "," << course;
   }
   out << "\n";

   // 3. Write each student row
   for (const auto &[id, student] : students) {
      out << id;
      for (const auto &course : allCourses) {
         auto it = student.grades.find(course);
         if (it != student.grades.end()) {
            out << "," << it->second;
         } else {
            out << ","; // blank for missing grade
         }
      }
      out << "\n";
   }

   out.close();
   std::cout << "Student grades exported to " << filename << "\n";
}

void mainMenu() {
   Student s;
   Admin a;
   int number = 0;
   cout << "1-Login as Student\n";
   cout << "2-Login as Admin\n";
   cout << "3-SignUp as Student\n";
   cout << "4-SignUP as Admin\n";
   cout << "0-Exit\n";
   cin >> number;
   switch (number) {
   case 1:
      s.loginStudent();
      break;
   case 2:
      a.loginAdmin();
      break;
   case 3:
      s.signUpStudent();
      break;
   case 4:
      a.signUpAdmin();
      break;
   case 0:
      return;
   default:
      break;
   }
}
int main() {
   load_students_from_file("data.json", students);
   load_admins_from_file("data.json", admins);
   loadCoursesFromFile("data.json", courses);
   update_student_grades_from_csv("grades.csv", students);

   mainMenu();

   save_students_to_file("data.json", students);
   save_admins_to_file("data.json", admins);
   save_students_grades_to_csv("grades.csv", students);
}
