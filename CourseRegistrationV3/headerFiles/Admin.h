#pragma once

#include "Common.h"

class Admin {
private:
    string username;
    string password;

public:
    Admin();
    Admin(string username, string password);

    // Getters
    string getUsername() const;
    string getPassword() const;

    // Setters
    void setUsername(const string& username);
    void setPassword(const string& password);

    void signUpAdmin();
    void loginAdmin();
    void addCourse(string code, string name, string instractor_name,
        string syllabus, float credit_hours);
    void updateCourseCode(const string& oldCode, const string& newCode);
    void updateCourseName(const string& code, const string& newName);
    void updateInstructor(const string& code, const string& newInstructor);
    void updateSyllabus(const string& code, const string& newSyllabus);
    void updateCreditHours(const string& code, float newCreditHours);
    void updateSemester(const string& code, int newSemester);

    void updateCourseDetails(const string& code,
        const string& newName = "",
        const string& newInstructor = "",
        const string& newSyllabus = "",
        float newCreditHours = -1,
        int newSemester = -1);
    void addPrerequisiteToCourse(const string& courseCode, const string& prerequisiteCode);
    void removePrerequisiteFromCourse(const string& courseCode, const string& prerequisiteCode);
    void makeRegisteredCoursesAsCompleted(string id, vector<string> codes);
    void uploadGradesFromCsv(string& filePath);
    void updateGrades(string id, string code, int grade);
};

