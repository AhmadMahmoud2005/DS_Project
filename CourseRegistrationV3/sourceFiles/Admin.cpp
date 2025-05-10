#include "../headerFiles/Admin.h"
#include "../headerFiles/Course.h"
#include "../headerFiles/Student.h"

Admin::Admin() {}

Admin::Admin(string username, string password) {
    this->username = username;
    this->password = password;
}

// Getters implementation
string Admin::getUsername() const {
    return username;
}

string Admin::getPassword() const {
    return password;
}

// Setters implementation
void Admin::setUsername(const string& username) {
    this->username = username;
}

void Admin::setPassword(const string& password) {
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
        while ((ch = _getch()) != '\n') {
            if (ch == 127 || ch == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password += ch;
                cout << '*';
            }
            cout.flush();
        }
        cout << endl;

        if (admins.find(username) == admins.end()) {
            cout << "Admin doesn't exists.\n";
            return;
        }
        else {
            auto it = admins.find(username);
            if (it->second.getPassword() != password) {
                cout << "wrong Password \n";
                input++;
                if (input == 3) {
                    cout << "your tried three wrong Passwords\n";
                    return;
                }
                continue;
            }
            else {
                cout << "Login Admin successfully\n";
                return;
            }
        }
    }
}

void Admin::addCourse(string code, string name, string instractor_name,
    string syllabus, float credit_hours) {
    Course course;
    course.setCode(code);
    course.setCreditHours(credit_hours);
    course.setName(name);
    course.setInstractorName(instractor_name);
    course.setSyllabus(syllabus);

    if (courses.find(code) != courses.end()) {
        cout << "This course is already exist!" << endl;
        return;
    }
    courses.insert(make_pair(code, course));
    cout << "Course added successfully!" << endl;
}
void Admin::updateCourseCode(const string& oldCode, const string& newCode) {
    if (courses.find(oldCode) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }

    if (courses.find(newCode) != courses.end()) {
        cout << "New course code already exists!\n";
        return;
    }

    Course temp = courses[oldCode];
    temp.setCode(newCode);
    courses.erase(oldCode);
    courses[newCode] = temp;
    cout << "Course code updated successfully.\n";
}

// تحديث اسم المقرر
void Admin::updateCourseName(const string& code, const string& newName) {
    if (courses.find(code) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }
    courses[code].setName(newName);
    cout << "Course name updated successfully.\n";
}

// تحديث اسم المحاضر
void Admin::updateInstructor(const string& code, const string& newInstructor) {
    if (courses.find(code) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }
    courses[code].setInstractorName(newInstructor);
    cout << "Instructor updated successfully.\n";
}

// تحديث الخطة الدراسية
void Admin::updateSyllabus(const string& code, const string& newSyllabus) {
    if (courses.find(code) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }
    courses[code].setSyllabus(newSyllabus);
    cout << "Syllabus updated successfully.\n";
}

// تحديث الساعات المعتمدة
void Admin::updateCreditHours(const string& code, float newCreditHours) {
    if (courses.find(code) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }
    courses[code].setCreditHours(newCreditHours);
    cout << "Credit hours updated successfully.\n";
}

// تحديث الفصل الدراسي
void Admin::updateSemester(const string& code, int newSemester) {
    if (courses.find(code) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }
    courses[code].setSemester(newSemester);
    cout << "Semester updated successfully.\n";
}

// دالة شاملة لتعديل عدة خصائص مرة واحدة
void Admin::updateCourseDetails(const string& code,
    const string& newName,
    const string& newInstructor,
    const string& newSyllabus,
    float newCreditHours,
    int newSemester) {
    if (courses.find(code) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }

    if (!newName.empty()) {
        courses[code].setName(newName);
    }

    if (!newInstructor.empty()) {
        courses[code].setInstractorName(newInstructor);
    }

    if (!newSyllabus.empty()) {
        courses[code].setSyllabus(newSyllabus);
    }

    if (newCreditHours != -1) {
        courses[code].setCreditHours(newCreditHours);
    }

    if (newSemester != -1) {
        courses[code].setSemester(newSemester);
    }

    cout << "Course details updated successfully.\n";
}
void Admin::addPrerequisiteToCourse(const string& courseCode, const string& prerequisiteCode) {
    if (courses.find(courseCode) == courses.end()) {
        cout << "The course is not found!" << endl;
        return;
    }

    if (courses.find(prerequisiteCode) == courses.end()) {
        cout << "The prerequisite course is not found!" << endl;
        return;
    }

    courses[courseCode].addPrerequisite(prerequisiteCode);
    cout << "Prerequisite added successfully!" << endl;
}

void Admin::removePrerequisiteFromCourse(const string& courseCode, const string& prerequisiteCode) {
    if (courses.find(courseCode) == courses.end()) {
        cout << "The course is not found!" << endl;
        return;
    }

    bool success = courses[courseCode].removePrerequisite(prerequisiteCode);
    if (!success) {
        cout << "This prerequisite wasn't found!" << endl;
    }
    else {
        cout << "Prerequisite removed successfully!" << endl;
    }
}

void Admin::makeRegisteredCoursesAsCompleted(string id, vector<string> codes)
{

}

void Admin::uploadGradesFromCsv(string& csvFile) {

    ifstream file(csvFile);
    if (!file.is_open()) {
        cout << "Failed to open file: " << csvFile << endl;
        return;
    }

    string line;
    vector<string> headers;
    unordered_map<string, unordered_map<string, int>> csvGrades;

    getline(file, line);
    stringstream headerStream(line);
    string col;
    while (getline(headerStream, col, ',')) {
        headers.push_back(col);
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        string student_id;
        unordered_map<string, int> grades;

        for (size_t i = 0; i < headers.size(); ++i) {
            getline(ss, cell, ',');

            if (i == 0) {
                student_id = cell;
            }
            else if (!cell.empty()) {
                try {
                    grades[headers[i]] = stoi(cell);
                }
                catch (const std::exception& e) {
                    cout << "Warning: Invalid grade value '" << cell << "' for student "
                        << student_id << ", course " << headers[i] << endl;
                }
            }
        }

        csvGrades[student_id] = grades;
    }

    for (const auto& student_id_and_grades : csvGrades) {
        const string& student_id = student_id_and_grades.first;
        const auto& grades_map = student_id_and_grades.second;

        if (students.count(student_id)) {
            Student& student = students[student_id];

            for (const auto& courseGrades : grades_map) {
                const string& courseCode = courseGrades.first;
                int grade = courseGrades.second;

                if (courses.find(courseCode) != courses.end()) {
                    student.setGrade(courseCode, grade);
                    student.addCompletedCourse(courseCode);

                    if (student.isRegisteredInCourse(courseCode)) {
                        student.removeRegisteredCourse(courseCode);
                    }
                }
                else {
                    cout << "Warning: Course '" << courseCode << "' not found in the system" << endl;
                }
            }

            double gpa = student.calculate_gpa();
            if (gpa >= 3.0)
                student.setTermCreditHours(21);
            else if (gpa >= 2.0)
                student.setTermCreditHours(18);
            else
                student.setTermCreditHours(15);
        }
        else {
            cout << "Warning: Student with ID '" << student_id << "' not found in the system" << endl;
        }
    }

    cout << "Grades updated from CSV successfully." << endl;
    cout << "Processed " << csvGrades.size() << " student records." << endl;
}

/*void Admin::uploadGradesFromCsv(string& csvFile) {
    ifstream file(csvFile);
    if (!file.is_open()) {
        cout << "Failed to open file: " << csvFile << endl;
        return;
    }

    string line;
    vector<string> headers;
    unordered_map<string, unordered_map<string, int>> csvGrades;

    // Parse headers
    getline(file, line);
    stringstream headerStream(line);
    string col;
    while (getline(headerStream, col, ',')) {
        headers.push_back(col);
    }

    // Parse CSV data
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        string student_id;
        unordered_map<string, int> grades;

        for (size_t i = 0; i < headers.size(); ++i) {
            getline(ss, cell, ',');
            if (i == 0)
                student_id = cell;
            else if (!cell.empty())
                grades[headers[i]] = stoi(cell);
        }
        csvGrades[student_id] = grades;
    }

    // Update students map
    for (const auto& student_id_and_grades : csvGrades) {
        const string& student_id = student_id_and_grades.first;
        const auto& grades_map = student_id_and_grades.second;

        if (students.count(student_id)) {
            Student& student = students[student_id];

            for (const auto& courseGrades : grades_map) {
                const string& courseCode = courseGrades.first;
                int grade = courseGrades.second;

                student.setGrade(courseCode, grade);
                student.addCompletedCourse(courseCode);
            }

            double gpa = student.calculate_gpa();
            if (gpa >= 3)
                student.setTermCreditHours(21);
            else if (gpa >= 2)
                student.setTermCreditHours(18);
            else
                student.setTermCreditHours(15);
        }
    }

    cout << "Grades updated from CSV.\n";
}*/

void Admin::updateGrades(string id, string code, int grade)
{
    if (students.find(id) == students.end())
    {
        cout << "This student not found!" << endl;
        return;
    }
    else
    {
        if (students[id].getCompletedCourses().find(code) == students[id].getCompletedCourses().end())
        {
            cout << "This course not found!" << endl;
            return;
        }
        else
        {
            students[id].setGrade(code, grade);
        }
    }

}

