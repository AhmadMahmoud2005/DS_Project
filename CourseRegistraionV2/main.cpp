#include "headerFiles/Files.h"
#include "headerFiles/globals.h"

int main() {
  load_students_from_file("dataFiles/data.json", students);
  load_admins_from_file("dataFiles/data.json", admins);
  loadCoursesFromFile("dataFiles/data.json", courses);
  update_student_grades_from_csv("dataFiles/grades.csv", students);

  mainMenu();

  save_students_to_file("dataFiles/data.json", students);
  save_admins_to_file("dataFiles/data.json", admins);
  save_students_grades_to_csv("dataFiles/grades.csv", students);
}
