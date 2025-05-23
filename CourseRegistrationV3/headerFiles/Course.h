#pragma once

#include "Common.h"

class Course {
private:
    string code;
    string name;
    string instractor_name;
    string syllabus;
    int semester;
    float credit_hours;
    unordered_set<string> prerequisites;

public:
    Course();

    // Getters
    string getCode() const;
    string getName() const;
    string getInstractorName() const;
    string getSyllabus() const;
    int getSemester() const;
    float getCreditHours() const;
    const unordered_set<string>& getPrerequisites() const;

    // Setters
    void setCode(const string& code);
    void setName(const string& name);
    void setInstractorName(const string& name);
    void setSyllabus(const string& syllabus);
    void setSemester(int semester);
    void setCreditHours(float hours);

    void addPrerequisite(const string& code);
    bool hasPrerequisite(const string& courseCode) const;
    bool removePrerequisite(const string& code);
};

