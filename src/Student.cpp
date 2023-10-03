#include "Student.h"

// CONSTRUCTORS
Student::Student(const std::string& email,
                 const std::string& password,
                 const std::string& fname,
                 const std::string& mname,
                 const std::string& lname,
                 int studentID)
               : User(email, password, fname, mname, lname),
                 studentID(studentID) {}
                 
Student::Student(const std::string& email,
                 const std::string& password,
                 const std::string& fname,
                 const std::string& mname,
                 const std::string& lname,
                 int studentID,
                 std::vector<std::string> uploadedDocuments)
               : User(email, password, fname, mname, lname),
                 studentID(studentID),
                 uploadedDocuments(uploadedDocuments) {}

// GETTER METHODS
int Student::getStudentID() const {
    return studentID;
};

const std::vector<int>& Student::getEnrolledSections() const {
    return enrolledSections;
}

const std::vector<std::string>& Student::getUploadedDocuments() const {
    return uploadedDocuments;
}

float Student::getGrade(int sectionID) const {
    auto it = grades.find(sectionID);
    if (it != grades.end()) {
        // if section is found, return associated grade;
        return it->second;
    } else {
        // !!! idk what to return if not found kekw
        return 0.0;
    }
}

std::string Student::getClassName() const {
    return "Student";
}

// SETTER METHOD
void Student::setEnrolledSection(int newSectionID) {
    enrolledSections.push_back(newSectionID);
}
void Student::setUploadedDocument(const std::string& newDocumentID) {
    uploadedDocuments.push_back(newDocumentID);
}

bool Student::operator==(const Student &compare) const {
    return studentID == compare.studentID;
}