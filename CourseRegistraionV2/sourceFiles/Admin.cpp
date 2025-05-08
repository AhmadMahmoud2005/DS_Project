#include "../headerFiles/globals.h"
#include <conio.h>
#include <iostream>
using namespace std;

Admin::Admin() {}
Admin::Admin(string username, string password) {
  this->username = username;
  this->password = password;
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
