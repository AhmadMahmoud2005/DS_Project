#pragma once
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


class Admin
{
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
