#include "Section.h"

// CONSTRUCTOR
Section::Section(int courseID,
                 int sectionID,
                 const std::string& sectionName,
                 int assignedFacultyID)
               : courseID(courseID),
                 sectionID(sectionID),
                 sectionName(sectionName),
                 assignedFacultyID(assignedFacultyID) {}

// GETTER METHODS
int Section::getCourseID() const {
    return courseID;
}

int Section::getSectionID() const {
    return sectionID;
}

std::string Section::getSectionName() const {
    return sectionName;
}

int Section::getAssignedFacultyID() const {
    return assignedFacultyID;
}

const std::vector<int>& Section::getEnrolledStudentIDs() const {
    return enrolledStudentIDs;
}
    
// SETTER METHODS
void Section::setSectionName(std::string newSectionName) {
    sectionName = newSectionName;
}

void Section::setAssignedFaculty(int newFacultyID) {
    assignedFacultyID = newFacultyID;
}

void Section::addEnrolledStudent(int studentID) {
    enrolledStudentIDs.push_back(studentID);
}

void Section::removeEnrolledStudent(int studentID) {
    enrolledStudentIDs.erase(std::remove(enrolledStudentIDs.begin(), enrolledStudentIDs.end(), studentID), enrolledStudentIDs.end());
}

bool Section::operator==(const Section &compare) const {
  return sectionID == compare.sectionID;
}