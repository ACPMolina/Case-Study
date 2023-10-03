#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"
#include "Student.h"
#include "json.hpp"

#include <string>
#include <vector>

class Faculty : public User {
public:
    // CONSTRUCTOR
    Faculty(const std::string& email,
            const std::string& password,
            const std::string& fname,
            const std::string& mname,
            const std::string& lname,
            int facultyID);

    Faculty() = default;

    // GETTER METHODS
    int getFacultyID() const;
    const std::vector<int>& getAssignedSections() const;

    // SETTER METHODS
    void setAssignedSection(int sectionID);
    std::string getClassName() const;

    // OTHER METHOD
    void setStudentGrade(Student& student, int sectionID, float newGrade);

    bool operator==(const Faculty &compare) const;

private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Faculty, email, password, fname, mname, lname, facultyID, assignedSections);
    
    int facultyID;
    std::vector<int> assignedSections;
};

#endif