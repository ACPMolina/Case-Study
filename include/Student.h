#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

#include <string>
#include <vector>
#include <map>

class Student : public User {
public:
    // CONSTRUCTOR
    Student(const std::string& username,
            const std::string& password,
            const std::string& fname,
            const std::string& mname,
            const std::string& lname,
            int studentID);

    Student(const std::string& username,
            const std::string& password,
            const std::string& fname,
            const std::string& mname,
            const std::string& lname,
            int studentID,
            std::vector<std::string> uploadedDocuments);


    Student() = default;
    // GETTER METHODS
    int getStudentID() const;
    const std::vector<int>& getEnrolledSections() const;
    const std::vector<std::string>& getUploadedDocuments() const;
    float getGrade(int sectionID) const;
    std::string getClassName() const;

    // SETTER METHODS
    void setEnrolledSection(int newSectionID);
    void setUploadedDocument(const std::string& newDocumentID);

    // Allow Faculty to set grade
    friend class Faculty;

    bool operator==(const Student &compare) const;

private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, email, password, fname, mname, lname, studentID, enrolledSections, uploadedDocuments, grades);
    
    int studentID;
    std::vector<int> enrolledSections;
    std::vector<std::string> uploadedDocuments;
    std::map<int, float> grades; // sectionID, grade
};

#endif