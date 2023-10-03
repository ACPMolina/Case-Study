#ifndef SECTION_H
#define SECTION_H

#include "json.hpp"

#include <string>
#include <vector>
#include <algorithm>

class Section {
public:
    // CONSTRUCTOR
    Section(int courseID,
            int sectionID,
            const std::string &sectionName,
            int assignedFacultyID);

    Section() = default;

    // GETTER METHODS
    int getCourseID() const;
    int getSectionID() const;
    std::string getSectionName() const;
    int getAssignedFacultyID() const;
    const std::vector<int>& getEnrolledStudentIDs() const;
    
    // SETTER METHODS
    void setSectionName(std::string sectionName);
    void setAssignedFaculty(int facultyID);
    void addEnrolledStudent(int studentID);
    void removeEnrolledStudent(int studentID);

    bool operator==(const Section &compare) const;

private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Section, courseID, sectionID, sectionName, assignedFacultyID, enrolledStudentIDs);

    int courseID;
    int sectionID;
    std::string sectionName;
    int assignedFacultyID;
    std::vector<int> enrolledStudentIDs;
};

#endif