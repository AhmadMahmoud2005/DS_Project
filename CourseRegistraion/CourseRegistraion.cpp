#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
using namespace std;

class Course{
public:
	string code;
	string name;
	vector<string> prerequisites;
	Course(string id,string name,vector<string>prerequisites) {
		this->code = id;
		this->name = name;
		this->prerequisites = prerequisites;
	}
};
class Student{
public:
	string id;
	string name;
	string password;
	unordered_set<string> completedCourses;
	unordered_set<string> registeredCourses;
	unordered_map<string, string> grades;//calculate GPA
	Student(){}//don't Delete it
	Student(string id,string name,string password){
		this->id = id;
		this->name = name;
		this->password = password;
	}
	void signUpStudent();
	void loginStudent();
};
class Admin{
public:
	string username;
	string password;
	Admin(){}//don't Delete it
	Admin(string username,string password){
		this->username = username;
		this->password = password;
	}
	void signUpAdmin();
	void loginAdmin();
};
unordered_map<string, Student> students;
unordered_map<string, Admin> admins;
void Student:: signUpStudent() {
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
void Student:: loginStudent() {
	string id,password;
	int input = 0;
	while (input<3)
	{
		cout << "enter Student ID: ";
		cin >> id;
		cout << "enter Student password: ";
		cin >> password;
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
void Admin:: signUpAdmin() {
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
void Admin:: loginAdmin() {
	string username, password;
	int input = 0;
	while (input<3)
	{
		cout << "Enter Admin Username: ";
		cin >> username;
		cout << "Enter Admin Password: ";
		cin >> password;

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
int main() {
	Student s;
	Admin a;
	int number = 0;
	char c='y';
	while (c!='n')
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





