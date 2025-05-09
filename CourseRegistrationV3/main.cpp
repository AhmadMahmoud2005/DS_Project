#include "headerFiles/FileOperations.h"

int main() {
   load_students_from_file("dataFiles/data.json", students);
   load_admins_from_file("dataFiles/data.json", admins);
   loadCoursesFromFile("dataFiles/data.json", courses);

   mainMenu();

   save_students_to_file("dataFiles/data.json", students);
   save_admins_to_file("dataFiles/data.json", admins);
}
