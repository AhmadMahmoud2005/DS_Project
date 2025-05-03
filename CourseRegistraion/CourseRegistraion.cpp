#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include <conio.h>
using namespace std;

class Course {
public:
	string code;
	string name;
	string instractor_name;
	string syllabus;
	float credit_hours;
	unordered_set<string> prerequisites;
	Course() {
		
		this->code = "";
		this->name = "";
		this->instractor_name = "";
		this->syllabus = "";
		this->credit_hours = 0.0;
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
	unordered_map<string, string> grades;//calculate GPA
	Student() {}//don't Delete it
	Student(string id, string name, string password) {
		this->id = id;
		this->name = name;
		this->password = password;
	}
	void signUpStudent();
	void loginStudent();
	void searchCourse();
	void RegisterForCourse(string name_or_code);

	bool checkPrerequisites(string name_or_code);
		
	
};
class Admin {
public:
	string username;
	string password;
	Admin() {}//don't Delete it
	Admin(string username, string password) {
		this->username = username;
		this->password = password;
	}
	void signUpAdmin();
	void loginAdmin();
	void addCourse(string code, string name, string instractor_name, string syllabus, float credit_hours);
	void setPrerequisites(string code , unordered_set<string> prerequistes);
};
unordered_map<string, Student> students;
unordered_map<string, Admin> admins;
unordered_map<string, Course> courses;
void Student::signUpStudent() {
	string id, name, password;
	cout << "enter Student ID: ";
	cin >> id;
	if (students.find(id) != students.end())//if exists a Student has this ID in H.Table
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
}
void Student::loginStudent() {
	string id, password;
	int input = 0;
	while (input < 3)
	{
		cout << "enter Student ID: ";
		cin >> id;
		cout << "enter Student password: ";
		password = "";
		char ch;
		while ((ch = _getch()) != '\r') {
			if (ch == '\b') {
				if (!password.empty()) {
					password.pop_back();
					cout << "\b \b";
				}
			}
			else {
				password += ch;
				cout << '*';
			}
		}
		cout << endl;
		if (students.find(id) == students.end())//if doesn't exist a Student has this ID in H.Table
		{
			cout << "the Student doesn't exist.\n";
			return;
		}
		else {
			auto it = students.find(id);
			if (it->second.password != password) {
				cout << "wrong Password \n";
				input++;
				if (input == 3) {
					cout << "your tried three wrong Passwords\n";
					return;
				}
				continue;
			}
			else
			{
				cout << "Login Student successfully\n";
				return;
			}
		}

	}

}
void Student::searchCourse() {
	cout << "Availabe Courses Are:" << endl;
	for (auto it = courses.begin(); it != courses.end(); it++)
	{
		cout << "Code: " << it->first << "\t" << "name: " << it->second.name << endl;
	}
}
void Student::RegisterForCourse(string code)
{
	bool checkprerequisites = checkPrerequisites(code);
	if (checkprerequisites)
		this->registeredCourses.insert(code);
	else
		cout << "You can't be registered to this course you have to complete prerequisites first!" << endl;
}
bool Student::checkPrerequisites(string code) {

	int completedCoursesSize = this->completedCourses.size();
	int prerequisitesSize = courses[code].prerequisites.size();
	if (prerequisitesSize > completedCoursesSize)
		return false;
	else
	{
		unordered_set<string>::iterator completedCoursesIt;
		unordered_set<string>::iterator prerequisitesIt;
	
		for (prerequisitesIt = courses[code].prerequisites.begin(); prerequisitesIt != courses[code].prerequisites.end(); prerequisitesIt++)
		{
			completedCoursesIt = this->completedCourses.find(*prerequisitesIt);
			if (completedCoursesIt == this->completedCourses.end())
				return false;
		}
		return true;
		
	}
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
	while (input < 3)
	{
		cout << "Enter Admin Username: ";
		cin >> username;
		cout << "Enter Admin Password: ";
		password = "";
		char ch;
		while ((ch = _getch()) != '\r') {
			if (ch == '\b') {
				if (!password.empty()) {
					password.pop_back();
					cout << "\b \b";
				}
			}
			else {
				password += ch;
				cout << '*';
			}
		}
		cout << endl;

		if (admins.find(username) == admins.end()) {
			cout << "Admin doesn't exists.\n";
			return;
		}
		else {
			auto it = admins.find(username);
			if (it->second.password != password) {
				cout << "wrong Password \n";
				input++;
				if (input == 3) {
					cout << "your tried three wrong Passwords\n";
					return;
				}
				continue;
			}
			else
			{
				cout << "Login Admin successfully\n";
				return;
			}
		}
	}
}
void Admin::addCourse(string code, string name, string instractor_name, string syllabus, float credit_hours) {
	Course course ;
	course.code = code;
	course.credit_hours = credit_hours;
	course.name = name;
	course.instractor_name = instractor_name;
	course.syllabus = syllabus;
	
	courses.insert(make_pair(code, course));

}
void Admin::setPrerequisites(string code , unordered_set <string> prerequisites) {
	courses[code].prerequisites = prerequisites;
}
int main() {
	/*Student s;*/
	//Course c1("123", "introduction", {});
	//courses.insert(make_pair("123",c1));
	//Course c2("246", "SP", {});
	//courses.insert(make_pair("246",c2));
	//Course c3("235", "DS", {});
	//courses.insert(make_pair("235",c3));
	//s.searchCourse();
	//return 0;//=============================>>>>stop
	Student s;
	Admin a;
	int number = 0;
	char c = 'y';
	while (c != 'n')
	{
		cout << "1-Login as Student\n";
		cout << "2-Login as Admin\n";
		cout << "3-SignUp as Student\n";
		cout << "4-SignUP as Admin\n";
		cout << "0-Exit\n";
		cin >> number;
		switch (number)
		{
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
			return 0;
		default:
			break;
		}
		cout << "Do you want to continue(y/n): ";
		cin >> c;
	}
}
