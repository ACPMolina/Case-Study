#include "Database.h"

#include "json.hpp"
#include "tabulate.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include <math.h>
#include <string.h>

#define DATADIR "../data/"
#define EXTDIR "../external/"

namespace fs = std::filesystem;

// CONSTRUCTOR
Database::Database() {}

// DECONSTRUCTOR
Database::~Database() {
    applicants.clear();
    students.clear();
    faculty.clear();
    staff.clear();
    admins.clear();
    courses.clear();
    sections.clear();
}

// RETURN METHODS
User* Database::findUserByEmail(const std::string& email) {
    for (auto& user : students) {
        if (user.getEmail() == email) {
            return &user;
        }
    }

    for (auto& user : faculty) {
        if (user.getEmail() == email) {
            return &user;
        }
    }

    for (auto& user : staff) {
        if (user.getEmail() == email) {
            return &user;
        }
    }

    for (auto& user : admins) {
        if (user.getEmail() == email) {
            return &user;
        }
    }

    return nullptr; // User not found.
}

User* Database::findUserByEmailAndPassword(const std::string& email, const std::string& password) {
    for (auto& user : students) {
        if (user.getEmail() == email && user.getPassword() == password) {
            return &user;
        }
    }

    for (auto& user : faculty) {
        if (user.getEmail() == email && user.getPassword() == password) {
            return &user;
        }
    }

    for (auto& user : staff) {
        if (user.getEmail() == email && user.getPassword() == password) {
            return &user;
        }
    }

    for (auto& user : admins) {
        if (user.getEmail() == email && user.getPassword() == password) {
            return &user;
        }
    }

    return nullptr; // User not found.
}

int Database::getLastID(const std::string& className) const {
    if (className == "Applicant") {
        if (applicants.empty()) {
            return 0;
        }
        return applicants.back().getApplicantID();
    } else if (className == "Student") {
        // Get the current time
        std::time_t now = std::time(nullptr);
        // Convert the current time to a std::tm structure
        std::tm current_time = *std::localtime(&now);
        // Extract the year from the std::tm structure
        int current_year = current_time.tm_year + 1900;

        if (students.empty()) {
            return current_year * 100000;
        }
        return (current_year * 100000) + (students.back().getStudentID() % 100000);
    } else if (className == "Faculty") {
        if (faculty.empty()) {
            return 0;
        }
        return faculty.back().getFacultyID();
    } else if (className == "Staff") {
        if (staff.empty()) {
            return 0;
        }
        return staff.back().getStaffID();
    } else if (className == "Admin") {
        if (admins.empty()) {
            return 0;
        }
        return staff.back().getStaffID();
    }  else if (className == "Course") {
        if (courses.empty()) {
            return 0;
        }
        return courses.back().getCourseID();
    }  else if (className == "Section") {
        // Get the current time
        std::time_t now = std::time(nullptr);
        // Convert the current time to a std::tm structure
        std::tm current_time = *std::localtime(&now);
        // Extract the year from the std::tm structure
        int current_year = current_time.tm_year + 1900;
        
        if (sections.empty()) {
            return (current_year % 100) * 1000;
        }
        return ((current_year % 100) * 1000) + (sections.back().getSectionID() % 1000);
    } else {
        std::cerr << "Passed className is not valid." << std::endl;
    }
    return -1;
}

Course* Database::findCourseByID(const std::string& search) {
    for (auto& course : courses) {
        if (std::to_string(course.getCourseID()) == search) {
            return &course;
        }
    }

    return nullptr;
}

// INSERT METHODS
void Database::insertApplicant(const Applicant& user) {
    applicants.push_back(user);
}

void Database::insertStudent(const Student& user) {
    students.push_back(user);
}

void Database::insertFaculty(const Faculty& user) {
    faculty.push_back(user);
}

void Database::insertStaff(const Staff& user) {
    staff.push_back(user);
}

void Database::insertAdmin(const Admin& user) {
    admins.push_back(user);
}

void Database::insertCourse(const Course& course) {
    courses.push_back(course);
}

void Database::insertSection(const Section& section) {
    sections.push_back(section);
}

// REMOVE METHODS
void Database::removeApplicant(const Applicant& user) {
    applicants.remove(user);
    saveList(DATADIR, "applicants", applicants);
}

void Database::removeStudent(const Student& user) {
    students.remove(user);
    saveList(DATADIR, "students", students);
}

void Database::removeFaculty(const Faculty& user) {
    faculty.remove(user);
    saveList(DATADIR, "faculty", faculty);
}

void Database::removeStaff(const Staff& user) {
    staff.remove(user);
    saveList(DATADIR, "staff", staff);
}

void Database::removeAdmin(const Admin& user) {
    admins.remove(user);
    saveList(DATADIR, "admins", admins);
}

void Database::removeCourse(const Course& course) {
    courses.remove(course);
    saveList(DATADIR, "courses", courses);
}

void Database::removeSection(const Section& section) {
    sections.remove(section);
    saveList(DATADIR, "sections", sections);
}

// DISPLAY METHODS
void Database::printListApplicants() {
    tabulate::Table table;
    table.format()
        .width(20)
        .corner(" ")
        .corner_color(tabulate::Color::cyan);

    table.add_row({"Applicant ID", "First Name", "Middle Name", "Last Name"});

    for (const auto& user : applicants) {
        table.add_row({std::to_string(user.getApplicantID()), user.getFName(), user.getMName(), user.getLName()});
    }
    
    std::cout << table << std::endl;
}

void Database::printListStudents() {
    tabulate::Table table;
    table.format()
        .width(20)
        .corner(" ")
        .corner_color(tabulate::Color::cyan);

    table.add_row({"Student ID", "Name", "Email"});
    
    for (const auto& user : students) {
        table.add_row({std::to_string(user.getStudentID()),
                       user.getLName() + ", " + user.getFName() + " " + user.getMName() + ".",
                       user.getEmail()});
    }
    
    std::cout << table << std::endl;
}

void Database::printListFaculty() {
    tabulate::Table table;
    table.format()
        .width(20)
        .corner(" ")
        .corner_color(tabulate::Color::cyan);

    table.add_row({"Faculty ID", "Name", "Email"});
    
    for (const auto& user : faculty) {
        table.add_row({std::to_string(user.getFacultyID()),
                       user.getLName() + ", " + user.getFName() + " " + user.getMName() + ".",
                       user.getEmail()});
    }
    
    std::cout << table << std::endl;
}

void Database::printListStaff() {
    tabulate::Table table;
    table.format()
        .width(20)
        .corner(" ")
        .corner_color(tabulate::Color::cyan);

    table.add_row({"Staff ID", "Name", "Email"});
    
    for (const auto& user : staff) {
        table.add_row({std::to_string(user.getStaffID()),
                       user.getLName() + ", " + user.getFName() + " " + user.getMName() + ".",
                       user.getEmail()});
    }
    
    std::cout << table << std::endl;
}

void Database::printListAdmin() {
    tabulate::Table table;
    table.format()
        .width(20)
        .corner(" ")
        .corner_color(tabulate::Color::cyan);

    table.add_row({"Admin ID", "Email"});
    
    for (const auto& user : admins) {
        table.add_row({std::to_string(user.getAdminID()), user.getEmail()});
    }
    std::cout << table << std::endl;
}

void Database::printListCourse() {
    ;
}

void Database::printListSection() {
    ;
}

void Database::printListSectionByCourse(const Course& course) {
    tabulate::Table table;
    table.format()
        .width(20)
        .corner(" ")
        .corner_color(tabulate::Color::cyan);

    table.add_row({"Section ID", "Section Name"});

    const std::vector<int>& sectionIDs = course.getSectionIDs();
    for (int sectionID : sectionIDs) {
        Section& section = *find_if(sections.begin(), sections.end(), [sectionID](const Section& section) {
            return section.getSectionID() == sectionID;
        });
        table.add_row({std::to_string(sectionID),
                       section.getSectionName()});
    }
    
    std::cout << table << std::endl;
}

void Database::printClassReport(const Section& section) {
    const std::vector<int>& enrolledStudentIDs = section.getEnrolledStudentIDs();
    tabulate::Table table;

    std::cout << "Section Name: " << section.getSectionName() << std::endl;
    std::cout << "Assigned Faculty: " << section.getAssignedFacultyID() << std::endl;

    table.format()
        .width(20)
        .corner(" ")
        .corner_color(tabulate::Color::cyan);
    table.add_row({"Student ID", "Grade"});
    for (int studentID : enrolledStudentIDs) {
        // Find the student object by ID
        Student* student = findStudentByID(studentID);

        if (student) {
            // Get the grade for this section
            float grade = student->getGrade(section.getSectionID());
            table.add_row({std::to_string(studentID), std::to_string(grade)});
        }
    }

    std::cout << "Class Report for Section: " << section.getSectionName() << std::endl;
    std::cout << table << std::endl;
}

// FILE METHODS
template <typename T>
void Database::saveList(const std::string& dataDir, const std::string& fileName, const std::list<T>& dataList) {
    // Create a JSON object for the list
    nlohmann::json listJson = dataList;

    // Save JSON object to JSON file
    std::ofstream listFile(dataDir + fileName + ".json");

    listFile << listJson.dump(4);

    // Close the file
    listFile.close();
}

void Database::saveDatabase(const std::string& dataDir) {
    saveList(dataDir, "applicants", applicants);
    saveList(dataDir, "students", students);
    saveList(dataDir, "faculty", faculty);
    saveList(dataDir, "staff", staff);
    saveList(dataDir, "admins", admins);
    saveList(dataDir, "courses", courses);
    saveList(dataDir, "sections", sections);
}

template <typename T>
void Database::loadList(const std::string& dataDir, const std::string& fileName, std::list<T>& dataList) {
    try {
        // Load JSON file into the corresponding list
        std::ifstream listFile(dataDir + fileName + ".json");
        nlohmann::json listJson;
        listFile >> listJson;

        // Deserialize JSON into list
        dataList = listJson.get<std::list<T>>();

        // Close the file
        listFile.close();
    } catch (const nlohmann::json::exception& e) {
        // Handle JSON parsing errors
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
}

void Database::loadDatabase(const std::string& dataDir) {
    loadList(dataDir, "applicants", applicants);
    loadList(dataDir, "students", students);
    loadList(dataDir, "faculty", faculty);
    loadList(dataDir, "staff", staff);
    loadList(dataDir, "admins", admins);
    loadList(dataDir, "courses", courses);
    loadList(dataDir, "sections", sections);
}

// OTHER METHODS

void Database::newApplicant(const std::string& fname, const std::string& mname, const std::string& lname, std::vector<std::string> uploadedDocuments) {
    int applicantID = getLastID("Applicant") + 1;
    
    insertApplicant(Applicant(fname, mname, lname, applicantID, uploadedDocuments));
    saveList(DATADIR, "applicants", applicants);
}

void Database::approveApplicant(const Applicant& user) {
    std::string fname = user.getFName();
    std::string mname = user.getMName();
    std::string lname = user.getLName();
    std::vector<std::string> uploadedDocuments = user.getUploadedDocuments();
    int studentID = getLastID("Student") + 1;
    std::string email = std::to_string(studentID) + "@elmwood.edu.ph";
    std::string password = lname + std::to_string(studentID);
    
    insertStudent(Student(email, password, fname, mname, lname, studentID, uploadedDocuments));
    removeApplicant(user);
    saveList(DATADIR, "applicants", applicants);
    saveList(DATADIR, "students", students);
}

void Database::createStudent(const std::string& fname, const std::string& mname, const std::string& lname) {
    int studentID = getLastID("Student") + 1;
    std::string email = std::to_string(studentID) + "@elmwood.edu.ph";
    std::string password = lname + std::to_string(studentID);
    
    insertStudent(Student(email, password, fname, mname, lname, studentID));
    saveList(DATADIR, "students", students);
}

void Database::createFaculty(const std::string& fname, const std::string& mname, const std::string& lname) {
    int facultyID = getLastID("Faculty") + 1;
    std::string email = "faculty" + std::to_string(facultyID) + "@elmwood.edu.ph";
    std::string password = lname + std::to_string(facultyID);
    
    insertFaculty(Faculty(email, password, fname, mname, lname, facultyID));
    saveList(DATADIR, "faculty", faculty);
}

void Database::createStaff(const std::string& fname, const std::string& mname, const std::string& lname) {
    int staffID = getLastID("Staff") + 1;
    std::string email = "staff" + std::to_string(staffID) + "@elmwood.edu.ph";
    std::string password = lname + std::to_string(staffID);
    
    insertStaff(Staff(email, password, fname, mname, lname, staffID));
    saveList(DATADIR, "staff", staff);
}

void Database::createAdmin(const std::string& email, const std::string& password) {
    int adminID = getLastID("Admin") + 1;
    
    insertAdmin(Admin(email, password, adminID));
    saveList(DATADIR, "admins", admins);
}

void Database::createCourse(const std::string& courseName) {
    int courseID = getLastID("Course") + 1;

    insertCourse(Course(courseID, courseName));
    saveList(DATADIR, "courses", courses);
}

void Database::createSection(int courseID, const std::string& sectionName) {
    int sectionID = getLastID("Section") + 1;
    
    insertSection(Section(courseID, sectionID, sectionName, 0));
    // Get the corresponding Course
    Course* course = findCourseByID(std::to_string(courseID));
    if (course) {
        // Add the section to the Course
        course->addSection(sectionID);
    saveList(DATADIR, "sections", sections);
    }
}

Section* Database::findSectionByID(const int& sectionID){
    for (auto& section : sections) {
        if (section.getSectionID() == sectionID) {
            return &section;
        }
    }return nullptr;
}

Student* Database::findStudentByID(const int& studentID){
    for (auto& student : students) {
        if (student.getStudentID() == studentID) {
            return &student;
        }
    }return nullptr;
}

Applicant* Database::findApplicantByID(const int& applicantID){
    for (auto& applicant : applicants) {
        if (applicant.getApplicantID() == applicantID) {
            return &applicant;
        }
    }return nullptr;
}

Faculty* Database::findFacultyByID(const int& facultyID){
    for (auto& user : faculty) {
        if (user.getFacultyID() == facultyID) {
            return &user;
        }
    }return nullptr;
}

void Database::addFacultyToSection(Section& section, Faculty& user) {
    int sectionID = section.getSectionID();
    int facultyID = user.getFacultyID();

    section.setAssignedFaculty(facultyID);
    user.setAssignedSection(sectionID);

    saveList(DATADIR, "sections", sections);
    saveList(DATADIR, "faculty", faculty);
}

void Database::addStudentToSection(Section& section, Student& user) {
    int sectionID = section.getSectionID();
    int studentID = user.getStudentID();

    section.addEnrolledStudent(studentID);
    user.setEnrolledSection(sectionID);

    saveList(DATADIR, "sections", sections);
    saveList(DATADIR, "students", students);
}

bool Database::checkFacultyInSection(const std::string& email, Section& section) {
    User* user = findUserByEmail(email);
    int sectionID = section.getSectionID();
    if (user) {
        Faculty* faculty = dynamic_cast<Faculty*>(user);
        std::vector<int> assignedSections = faculty->getAssignedSections();
        // Check if the sectionID is in the list of assigned sections
        for (int assignedSectionID : assignedSections) {
            if (assignedSectionID == sectionID) {
                return true; // Faculty is assigned to this section
            }
        }
    }
    return false; // User not found
}

std::string Database::uploadDocument(const std::string& email) {
    // Get the current timestamp in nanoseconds
    auto now = std::chrono::high_resolution_clock::now();
    std::string timestamp = std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count());

    // Create a directory with the timestamp in "../data/uploads"
    std::string datadir = DATADIR;
    std::string uploadDir = datadir + "uploads/" + timestamp;
    fs::create_directories(uploadDir);

    // Copy documents from "../external" to the new folder
    std::string externalDir = EXTDIR;
    for (const auto& entry : fs::directory_iterator(externalDir)) {
        std::string sourcePath = entry.path().string();
        std::string sourceName = entry.path().filename().string();
        fs::copy(sourcePath, uploadDir + "/" + sourceName);
    }

    // Check if user is an Applicant or Student then set the uploadedDocument
    User* user = findUserByEmail(email);
    if (user && user->getClassName() == "Student") {
        Student* student = dynamic_cast<Student*>(user);
        student->setUploadedDocument(timestamp);
        saveList(DATADIR, "students", students);
        std::cout << "Document has been uploaded to " << uploadDir << std::endl;
    }
    return timestamp;
}