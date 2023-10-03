#ifndef COURSE_H
#define COURSE_H

#include "json.hpp"

#include <string>
#include <vector>

class Course {
public:
    // CONSTRUCTOR
    Course(int courseID,
           const std::string& courseName);

    Course() = default;

    // GETTER METHODS
    int getCourseID() const;
    std::string getCourseName() const;
    const std::vector<int>& getSectionIDs() const;

    // SETTER METHODS
    void setCourseName(std::string courseName);
    void addSection(int sectionID);
    // void removeSection(int sectionID);

    bool operator==(const Course &compare) const;

private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Course, courseID, courseName, sectionIDs);

    int courseID;
    std::string courseName;
    std::vector<int> sectionIDs;
};

#endif