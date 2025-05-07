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

class Course 
{
public:
	string code;
	string name;
	string instractor_name;
	string syllabus;
	string semester;
	float credit_hours;
	unordered_set<string> prerequisites;
	Course();
}