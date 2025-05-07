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


Course::Course() {

    this->code = "";
    this->name = "";
    this->instractor_name = "";
    this->syllabus = "";
    this->credit_hours = 0.0;
    this->semester = "";
}
