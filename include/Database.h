#ifndef DATABASE_H
#define DATABASE_H

#include "User.h"
#include "Applicant.h"
#include "Student.h"
#include "Faculty.h"
#include "Staff.h"
#include "Admin.h"
#include "Course.h"
#include "Section.h"

#include <string>
#include <vector>
#include <list>

class Database {
public:
    // CONSTRUCTOR
    Database();

    // DECONSTRUCTOR
    ~Database();

    // RETURN METHODS
    User* findUserByEmail(const std::string& email);
    User* findUserByEmailAndPassword(const std::string& email,
                                     const std::string& password);
    int getLastID(const std::string& className) const;
    Course* findCourseByID(const std::string& search);

    // INSERT METHODS
    void insertApplicant(const Applicant& user);
    void insertStudent(const Student& user);
    void insertFaculty(const Faculty& user);
    void insertStaff(const Staff& user);
    void insertAdmin(const Admin& user);
    void insertCourse(const Course& course);
    void insertSection(const Section& section);

    // REMOVE METHODS
    void removeApplicant(const Applicant& user);
    void removeStudent(const Student& user);
    void removeFaculty(const Faculty& user);
    void removeStaff(const Staff& user);
    void removeAdmin(const Admin& user);
    void removeCourse(const Course& course);
    void removeSection(const Section& section);

    // DISPLAY METHODS
    void printListApplicants();
    void printListStudents();
    void printListFaculty();
    void printListStaff();
    void printListAdmin();
    void printListCourse();
    void printListSection();
    void printListSectionByCourse(const Course& course);
    void printClassReport(const Section& section);

    // FILE METHODS
    template <typename T>
    void saveList(const std::string& dataDir,
                  const std::string& fileName,
                  const std::list<T>& dataList);
    void saveDatabase(const std::string& dataDir);

    template <typename T>
    void loadList(const std::string& dataDir,
                  const std::string& fileName,
                  std::list<T>& dataList);
    void loadDatabase(const std::string& dataDir);

    // OTHER METHODS
    void newApplicant(const std::string& fname,
                      const std::string& mname,
                      const std::string& lname,
                      std::vector<std::string> uploadedDocuments);
    void approveApplicant(const Applicant& user);
    void createStudent(const std::string& fname,
                       const std::string& mname,
                       const std::string& lname);
    void createFaculty(const std::string& fname,
                       const std::string& mname,
                       const std::string& lname);
    void createStaff(const std::string& fname,
                     const std::string& mname,
                     const std::string& lname);
    void createAdmin(const std::string& email,
                     const std::string& password);
    void createCourse(const std::string& courseName);
    void createSection(int courseID, const std::string& sectionName);
    Section* findSectionByID(const int& sectionID);
    Student* findStudentByID(const int& studentID);
    Applicant* findApplicantByID(const int& applicantID);
    void addFacultyToSection(Section& section, Faculty& faculty);
    void addStudentToSection(Section& section, Student& user);
    Faculty* findFacultyByID(const int& facultyID);
    bool checkFacultyInSection(const std::string& email, Section& section);
    std::string uploadDocument(const std::string& email);

private:
    std::list<Applicant> applicants;
    std::list<Student> students;
    std::list<Faculty> faculty;
    std::list<Staff> staff;
    std::list<Admin> admins;
    std::list<Course> courses;
    std::list<Section> sections;
};

#endif