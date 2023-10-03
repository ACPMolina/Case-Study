#include "Course.h"

// CONSTRUCTOR
Course::Course(int courseID,
               const std::string& courseName)
             : courseID(courseID),
               courseName(courseName) {}

// GETTER METHODS
int Course::getCourseID() const {
    return courseID;
}

std::string Course::getCourseName() const {
    return courseName;
}

const std::vector<int>& Course::getSectionIDs() const {
    return sectionIDs;
}

// SETTER METHODS
void Course::setCourseName(std::string newCourseName) {
    courseName = newCourseName;
}


void Course::addSection(int sectionID) {
    sectionIDs.push_back(sectionID);
}

// void Course::removeSection(int sectionID) {
//     sectionIDs.erase(std::remove(sectionIDs.begin(), sectionIDs.end(), sectionID), sectionIDs.end());
// }

bool Course::operator==(const Course &compare) const{
  return courseID == compare.courseID;
}