#include "../headerFiles/globals.h"
#include <conio.h>
#include <iostream>

using namespace std;

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
      if (ch == 127 || ch == '\b') {  // handle Backspace (127 on Linux)
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
