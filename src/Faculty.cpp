#include "Faculty.h"

// CONSTRUCTORS
Faculty::Faculty(const std::string& email,
                 const std::string& password,
                 const std::string& fname,
                 const std::string& mname,
                 const std::string& lname,
                 int facultyID)
               : User(email, password, fname, mname, lname),
                 facultyID(facultyID) {}

// GETTER METHODS
int Faculty::getFacultyID() const {
    return facultyID;
}

const std::vector<int>& Faculty::getAssignedSections() const {
    return assignedSections;
}

// SETTER METHODS
void Faculty::setAssignedSection(int newSectionID) {
    assignedSections.push_back(newSectionID);
}

std::string Faculty::getClassName() const {
    return "Faculty";
}

// OTHER METHOD
void Faculty::setStudentGrade(Student& student, int sectionID, float newGrade) {
    student.grades[sectionID] = newGrade;
}

bool Faculty::operator==(const Faculty &compare) const{
  return facultyID == compare.facultyID;
}