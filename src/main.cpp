#include <iostream>
#include <fstream>
#include <cstdlib>   // For system() function
#include <string>
#include <vector>

#include "Database.h"
#ifdef _WIN32
#include <conio.h>   // For _getch() function on Windows
#else
#include <termios.h> // For tcsetattr() and tcgetattr() on POSIX systems
#include <unistd.h>  // For read() and STDIN_FILENO on POSIX systems
#endif

int menuMain();
void menuEnrollment();
void menuLogin();
void menuStudent(const std::string& email);
void menuFaculty(const std::string& email);
void menuStaff(const std::string& email);
void menuAdmin(const std::string& email);
void menuCreateUser();
void consoleClear();
void consolePause();

Database db;

int main() {
    // Load the latest database files
    db.loadDatabase("../data/");
    int choice;
    
    do {
        choice = menuMain();
        switch (choice) {
            case 1: // Enrollment Page
                menuEnrollment();
                break;
            case 2: // Login Page
                menuLogin();
                break;
            case 3: // Exit'
                db.saveDatabase("../data/");
                db.~Database();
                return 0;
            case 4:
                menuFaculty("testemail");
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 3);
}

int menuMain() {
    int choice = 0;
    while ( !(choice > 0 && choice < 5) ) {
        consoleClear();
        std::cout << "\033[1;32m";
        std::cout << "==============================" << std::endl;
        std::cout << "|     "
                  << "\033[1;33m"
                  << "ELMWOOD UNIVERSITY"
                  << "\033[0m"
                  << "\033[1;32m"
                  << "     |" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "\033[0m";

        std::cout << "\033[1;35m" << "1 " << "\033[0m"
                  << "Enrollment Page" << std::endl;
        std::cout << "\033[1;35m" << "2 " << "\033[0m"
                  << "Login Page" << std::endl;
        std::cout << "\033[1;35m" << "3 " << "\033[0m"
                  << "Exit" << std::endl;
        
        std::cout << std::endl;
        std::cout << "\033[1;34m"
                  << "Enter your choice: "
                  << "\033[0m";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

void menuEnrollment() {
    std::string fname = "";
    std::string mname = "";
    std::string lname = "";
    std::vector<std::string> uploadedDocuments;
    
    int choice = 0;
    while ( choice != 4 ) {
        consoleClear();
        std::cout << "\033[1;32m";
        std::cout << "==============================" << std::endl;
        std::cout << "|          ENROLLMENT        |" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "\033[0m";
        
        std::cout << std::endl;
        std::cout << "First Name:  " << fname << std::endl;
        std::cout << "Middle Name: " << mname << std::endl;
        std::cout << "Last Name:   " << lname << std::endl;
        std::cout << std::endl;
        
        std::cout << "\033[1;32m" << "1 " << "\033[0m"
                  << "Fill-out Information" << std::endl;
        std::cout << "\033[1;32m" << "2 " << "\033[0m"
                  << "Upload Documents" << std::endl;
        std::cout << "\033[1;32m" << "3 " << "\033[0m"
                  << "Submit Application" << std::endl;
        std::cout << "\033[1;32m" << "4 " << "\033[0m"
                  << "Back to Main Menu" << std::endl;
        
        std::cout << std::endl;
        std::cout << "\033[1;34m"
                  << "Enter your choice: "
                  << "\033[0m";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Fill-out Information
                consoleClear();
                std::cout << "Enter First Name:  ";
                std::getline(std::cin, fname);
                std::cout << "Enter Middle Name: ";
                std::getline(std::cin, mname);
                std::cout << "Enter Last Name:   ";
                std::getline(std::cin, lname);
                break;
            case 2: // Upload Documents
            {
                std::cout << "Selected Upload Documents" << std::endl;
                std::cout << "All files in \"external/\" folder will be uploaded." << std::endl;
                std::cout << "Do you want to proceed? (Y/N): ";
                std::string confirm;
                std::cin >> confirm;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (confirm == "y" || confirm == "Y") {
                    std::string documentTimestamp = db.uploadDocument("Applicant");
                    uploadedDocuments.push_back(documentTimestamp);
                } else {
                    std::cout << "Cancelled uploading documents." << std::endl;
                }
                
                consolePause();
                break;
            }
            case 3: // Submit Application
                db.newApplicant(fname, mname, lname, uploadedDocuments);
                std::cout << "Successfully submitted application!" << std::endl;
                choice = 4;
                consolePause();
                break;
            case 4: // Back to Main Menu
                break;
            default:
                std::cerr << "\033[1;31m"
                          << "Invalid choice. Please try again." << std::endl
                          << "\033[0m";
        }
    }
}
void menuLogin() {
    std::string email = "";
    std::string password = "";
    User* user = nullptr;
    
    int choice = 0;
    while ( choice != 4 ) {
        consoleClear();
        std::cout << "\033[1;32m";
        std::cout << "==============================" << std::endl;
        std::cout << "|         LOGIN PAGE         |" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "\033[0m";
        
        std::cout << std::endl;
        std::cout << "Email:    " << email    << std::endl;
        std::cout << "Password: " << password << std::endl;
        std::cout << std::endl;
        
        std::cout << "1. Enter Email" << std::endl;
        std::cout << "2. Enter Password" << std::endl;
        std::cout << "3. Login" << std::endl;
        std::cout << "4. Back to Main Menu" << std::endl;
        
        std::cout << std::endl;
        std::cout << "\033[1;34m"
                  << "Enter your choice: "
                  << "\033[0m";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: // Enter Email
                consoleClear();
                std::cout << "Enter Email: ";
                std::getline(std::cin, email);
                break;
            case 2: // Enter Password
                consoleClear();
                std::cout << "Enter Password: ";
                std::getline(std::cin, password);
                break;
            case 3: // Login
                user = db.findUserByEmailAndPassword(email, password);
                
                if (!user) {
                    std::cout << std::endl;
                    std::cout << "User not found. Please check if your email and password are correct." << std::endl;
                } else if ( user->getClassName() == "Student" ) {
                    menuStudent(email);
                } else if ( user->getClassName() == "Faculty" ) {
                    menuFaculty(email);
                } else if ( user->getClassName() == "Staff" ) {
                    menuStaff(email);
                } else if ( user->getClassName() == "Admin" ) {
                    menuAdmin(email);
                } else {
                    std::cerr << "\033[1;31m"
                              << "Warning! User does not have a valid role." << std::endl
                              << "\033[0m";
                }
                break;
            case 4: // Back to Main Menu
                break;
            default:
                std::cerr << "\033[1;31m"
                          << "Invalid choice. Please try again." << std::endl
                          << "\033[0m";
        }
    }
}

void menuStudent(const std::string& email) {
    int choice = 0;
    while ( choice != 3 ) {
        consoleClear();
        std::cout << "\033[1;32m";
        std::cout << "==============================" << std::endl;
        std::cout << "|           STUDENT          |" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "\033[0m";
        
        std::cout << "1. Submit Documents" << std::endl;
        std::cout << "2. See Information" << std::endl;
        std::cout << "3. Logout" << std::endl;
        
        std::cout << std::endl;
        std::cout << "\033[1;34m"
                  << "Enter your choice: "
                  << "\033[0m";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Submit Documents
            {
                std::cout << "Selected Submit Documents" << std::endl;
                std::cout << "All files in \"external/\" folder will be uploaded." << std::endl;
                std::cout << "Do you want to proceed? (Y/N): ";
                std::string confirm;
                std::cin >> confirm;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (confirm == "y" || confirm == "Y") {
                    db.uploadDocument(email);
                    std::cout << std::endl;
                    std::cout << "Documents have been uploaded." << std::endl;
                } else {
                    std::cout << "Cancelled uploading documents." << std::endl;
                }
                
                consolePause();
                break;
            }
            case 2: // See Information
            {
                User* user = db.findUserByEmail(email);

                if (user && user->getClassName() == "Student") {
                    Student* student = dynamic_cast<Student*>(user);

                    if (student) {
                        // Display Student Information
                        std::cout << "Student ID: " << student->getStudentID() << std::endl;
                        std::cout << "Full Name: " << student->getFullName() << std::endl;

                        const std::vector<int>& assignedSections = student->getEnrolledSections();
                        std::cout << "Assigned Sections:" << std::endl;
                        for (int sectionID : assignedSections) {
                            Section* section = db.findSectionByID(sectionID);
                            if (section) {
                                std::cout << "  - Section Name: " << section->getSectionName() << std::endl;

                                // Get the grade for this section
                                float grade = student->getGrade(sectionID);
                                std::cout << "    Grade: " << grade << std::endl;
                            }
                        }
                    } else {
                        std::cout << "Invalid student data." << std::endl;
                    }
                }

                consolePause();
                break;
            }
            case 3: // Logout
                break;
            default:
                std::cerr << "\033[1;31m"
                          << "Invalid choice. Please try again." << std::endl
                          << "\033[0m";
        }
    }
}

void menuFaculty(const std::string& email) {
    int choice = 0;
    while ( choice != 4 ) {
        consoleClear();
        std::cout << "\033[1;32m";
        std::cout << "==============================" << std::endl;
        std::cout << "|           FACULTY          |" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "\033[0m";
        
        std::cout << "1. Input Student Grades" << std::endl;
        std::cout << "2. Search Student Records" << std::endl;
        std::cout << "3. Generate Class Report" << std::endl;
        std::cout << "4. Logout" << std::endl;
        
        std::cout << std::endl;
        std::cout << "\033[1;34m"
                  << "Enter your choice: "
                  << "\033[0m";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Input Student Grades
            {
                int sectionID, studentID;
                float grade;
                std::cout << "Selected Input Student Grades" << std::endl;
                User* match = db.findUserByEmail(email);
                if (match) {
                    Faculty* faculty = dynamic_cast<Faculty*>(match);
                    if (faculty) {
                        //Display the assigned sections
                        const std::vector<int>& assignedSections = faculty->getAssignedSections();
                        std::cout << "Assigned Sections" << std::endl;
                        for (auto sections : assignedSections) {
                            std::cout << "Sections: " << sections << std::endl;
                        }
                        std::cout << "Enter the Section ID to Grade: ";
                        std::cin >> sectionID;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        //Display enrolled students in section
                        Section* sectionMatch = db.findSectionByID(sectionID);
                        if (sectionMatch) {
                            Section* section = dynamic_cast<Section*>(sectionMatch);
                            // Check if faculty is assigned to that section or not
                            bool assigned = db.checkFacultyInSection(email, *section);
                            if (assigned) {
                                std::cout << "Students" << std::endl;
                                const std::vector<int>& enrolledStudentIDs = section->getEnrolledStudentIDs();
                                for(auto students : enrolledStudentIDs){
                                    std::cout << "Students: " << students << std::endl;
                                }
                                std::cout << "Enter the Student ID to Grade: ";
                                std::cin >> studentID;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                                //Search for the student using the ID
                                Student* studentMatch = db.findStudentByID(studentID);
                                if (studentMatch) {
                                    Student* student = dynamic_cast<Student*>(studentMatch);
                                    if (studentMatch) {
                                        std::cout << "Input the grade: ";
                                        std::cin >> grade;
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        faculty->setStudentGrade(*student, section->getSectionID(), grade);
                                        std::cout << "Grade: " << student->getGrade(section->getSectionID()) << std::endl;
                                        db.saveDatabase("../data/");
                                    }
                                } else {
                                    std::cout << "No student with the inputted ID has been found." << std::endl;
                                    continue;
                                }
                            }
                        } else {
                            std::cout << "No section with the inputted ID has been found." << std::endl;
                            continue;
                        }
                    }
                }
                consolePause();
                break;
            }
            case 2: // Search Student Records
            {
                std::string email;
                std::cout << "Enter student email: ";
                std::cin >> email;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                User* match = db.findUserByEmail(email);
                if(match){
                    Student* student = dynamic_cast<Student*>(match);
                    std::cout << "StudentID: " << student->getStudentID() << "Name: " << student->getFullName() << std::endl;
                }
            }
            consolePause();
            break;
            case 3: // Generate Class Report
            {
                do {
                    std::cout << "Selected Generate Class Report" << std::endl;
                    std::cout << "Enter Section ID to generate class report for: ";
                    int sectionID;
                    std::cin >> sectionID;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Section* section = db.findSectionByID(sectionID);

                    if (section) {
                        // Check if faculty is assigned to that section or not
                        bool assigned = db.checkFacultyInSection(email, *section);
                        if (assigned) {
                            db.printClassReport(*section);
                        } else {
                            std::cout << "Cannot access section that is not assigned to faculty" << std::endl;
                        }
                    } else {
                        std::cout << "Section not found." << std::endl;
                        consolePause();
                        continue;
                    }

                    consolePause();
                    break;
                } while (true);
            }
            case 4: // Logout
                break;
            default:
                std::cerr << "\033[1;31m"
                          << "Invalid choice. Please try again." << std::endl
                          << "\033[0m";
        }
    }
}

void menuStaff(const std::string& email) {
    int choice = 0;
    while ( choice != 4 ) {
        consoleClear();
        std::cout << "\033[1;32m";
        std::cout << "==============================" << std::endl;
        std::cout << "|            STAFF           |" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "\033[0m";
        
        std::cout << "1. Display Applicants (Enrollment)" << std::endl;
        std::cout << "2. Search Student Records" << std::endl;
        std::cout << "3. Generate Class/Course Report" << std::endl;
        std::cout << "4. Logout" << std::endl;
        
        std::cout << std::endl;
        std::cout << "\033[1;34m"
                  << "Enter your choice: "
                  << "\033[0m";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Display Applicants (Enrollment)
            {
                do {
                    consoleClear();
                    int applicantID;
                    db.printListApplicants();
                    std::cout << "Enter the Applicant ID: ";
                    std::cin >> applicantID;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    User* match = db.findApplicantByID(applicantID);
                        if(match){
                            Applicant* applicant = dynamic_cast<Applicant*>(match);
                            if(applicant){
                                db.approveApplicant(*applicant);
                                std::cout << "Applicant Approved!" << std::endl;
                            }
                        }else{
                            std::cerr << "Applicant Not Found! Please try again." << std::endl;
                        }
                    break;
                } while (true);
                break;
            }
            case 2: // Search Student Records
            {
                std::string match;
                std::cout << "Enter student email: ";
                std::cin >> match;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                User* user = db.findUserByEmail(match);

                if (user && user->getClassName() == "Student") {
                    Student* student = dynamic_cast<Student*>(user);
                    std::cout << "Student ID: " << student->getStudentID() << std::endl;
                    std::cout << "Full Name: " << student->getFullName() << std::endl;
                    const std::vector<int>& assignedSections = student->getEnrolledSections();
                    for (int sectionID : assignedSections) {
                        Section* section = db.findSectionByID(sectionID);
                        if (section) {
                            std::cout << "Section Name: " << section->getSectionName() << std::endl;

                            // Get the grade for this section
                            float grade = student->getGrade(sectionID);
                            std::cout << "Grade: " << grade << std::endl;
                        }
                    }
                    consolePause();
                } else {
                    std::cout << "No student with the inputted email found." << std::endl;
                    consolePause();
                    continue;
                }
                break;
            }
            case 3: // Generate Class/Course Report
            {
                do {
                    consoleClear();
                    std::cout << "Selected Generate Class Report" << std::endl;
                    std::cout << "Enter Section ID to generate class report for: ";
                    int sectionID;
                    std::cin >> sectionID;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    Section* section = db.findSectionByID(sectionID);

                    if (section) {
                        db.printClassReport(*section);
                    } else {
                        std::cout << "Section not found." << std::endl;
                        consolePause();
                        continue;
                    }

                    consolePause();
                    break;
                } while (true);
                break;
            }
            case 6: //Add Faculty to Section
                {
                    //Check if course exists
                    std::string courseID, email;
                    int sectionID;
                    std::cout << "Enter the course: ";
                    std::cin >> courseID;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Course* match = db.findCourseByID(courseID);
                    if (match) {
                        std::cout << std::endl;
                        std::cout << "Course " << courseID << " has been found." << std::endl;
                        std::cout << "Course Name: " << match->getCourseName() << std::endl;
                        std::cout << std::endl;
                        std::cout << "Sections in this Course:" << std::endl;
                        db.printListSectionByCourse(*match);
                        consolePause();
                        std::cout << "Enter the section: ";
                        std::cin >> sectionID;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        Section* sectionMatch = db.findSectionByID(sectionID);
                        if(sectionMatch){
                            std::cout << "Enter the faculty email: ";
                            std::cin >> email;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            User* userMatch = db.findUserByEmail(email);
                            if(userMatch){
                                Faculty* faculty = dynamic_cast<Faculty*>(userMatch);
                                faculty->setAssignedSection(sectionMatch->getSectionID());

                            }
                        }
                        break;
                    } else {
                        std::cout << std::endl;
                        std::cerr << "No match has been found." << std::endl;
                        consolePause();
                        continue;
                    }
                
                break;
                }
            case 4: // Logout
                break;
            default:
                std::cerr << "\033[1;31m"
                          << "Invalid choice. Please try again." << std::endl
                          << "\033[0m";
        }
    }
}

void menuAdmin(const std::string& email) {
    int choice = 0;
    while ( choice != 8 ) {
        consoleClear();
        std::cout << "\033[1;32m";
        std::cout << "==============================" << std::endl;
        std::cout << "|            ADMIN           |" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "\033[0m";
        
        std::cout << "1. Create User" << std::endl;
        std::cout << "2. Remove User" << std::endl;
        std::cout << "3. Create Course" << std::endl;
        std::cout << "4. Find Existing Course/Section" << std::endl;
        std::cout << "5. Create Section" << std::endl;
        std::cout << "6. Add Faculty to Section" << std::endl;
        std::cout << "7. Add Student to Section" << std::endl;
        std::cout << "8. Logout" << std::endl;
        
        std::cout << std::endl;
        std::cout << "\033[1;34m"
                  << "Enter your choice: "
                  << "\033[0m";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl;

        switch (choice) {
            case 1: // Create User
                menuCreateUser();
                break;
            case 2: // Remove User
            {
                consoleClear();
                std::cout << "Selected Remove User" << std::endl;
                std::cout << "Enter the email of the user to remove: ";
                std::string search;
                std::cin >> search;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                // Implement user removal logic here
                User* match = db.findUserByEmail(search);
                if (match) {
                    std::cout << std::endl;
                    std::cout << "User " << search << " has been found." << std::endl;
                    std::cout << "User Name: " << match->getFullName() << std::endl;
                    std::cout << std::endl;
                    std::cout << "Are you sure you want to remove this user? (Y/N): ";
                    std::string confirm;
                    std::cin >> confirm;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (confirm == "y" || confirm == "Y") {
                        // Determine the type of user and call the appropriate remove function
                        if (dynamic_cast<Student*>(match)) {
                            db.removeStudent(*dynamic_cast<Student*>(match));
                        } else if (dynamic_cast<Faculty*>(match)) {
                            db.removeFaculty(*dynamic_cast<Faculty*>(match));
                        } else if (dynamic_cast<Staff*>(match)) {
                            db.removeStaff(*dynamic_cast<Staff*>(match));
                        } else if (dynamic_cast<Admin*>(match)) {
                            db.removeAdmin(*dynamic_cast<Admin*>(match));
                        }
                        std::cout << std::endl;
                        std::cout << "User has been removed." << std::endl;
                    } else {
                        std::cout << "User removal cancelled." << std::endl;
                    }
                    consolePause();
                    continue;
                } else {
                    std::cout << std::endl;
                    std::cerr << "No match has been found." << std::endl;
                    consolePause();
                    continue;
                }

                consolePause();
                break;
            }
            case 3: // Create Course
            {
                consoleClear();
                std::cout << "Selected Create Course" << std::endl;
                std::cout << "Enter Course Name: ";
                std::string courseName;
                std::getline(std::cin, courseName);
                db.createCourse(courseName);
                std::cout << std::endl;
                std::cout << "Course has been created." << std::endl;
                consolePause();
                break;
            }
            case 4: // Find Existing Course
            {
                do {
                    consoleClear();
                    std::cout << "Selected Find Existing Course" << std::endl;
                    std::cout << "Search For Existing Course (0 to exit): ";
                    std::string search;
                    std::getline(std::cin, search);

                    if (search == "0") break;
                    //Check if course exists
                    Course* match = db.findCourseByID(search);
                    if (match) {
                        std::cout << std::endl;
                        std::cout << "Course " << search << " has been found." << std::endl;
                        std::cout << "Course Name: " << match->getCourseName() << std::endl;
                        std::cout << std::endl;
                        std::cout << "Sections in this Course:" << std::endl;
                        db.printListSectionByCourse(*match);
                        consolePause();
                        break;
                    } else {
                        std::cout << std::endl;
                        std::cerr << "No match has been found." << std::endl;
                        consolePause();
                        continue;
                    }
                } while (true);
                break;
            }
            case 5: // Create Section
            {
                int courseID;
                do {
                    std::cout << "Selected Create Section" << std::endl;
                    std::cout << "Search For Existing Course (0 to exit): ";
                    std::string search;
                    std::getline(std::cin, search);

                    if (search == "0") break;
                    //Check if course exists
                    Course* match = db.findCourseByID(search);
                    if (match) {
                        courseID = match->getCourseID();
                    } else {
                        std::cout << std::endl;
                        std::cerr << "No match has been found." << std::endl;
                        consolePause();
                        continue;
                    }
                    std::cout << std::endl;
                    std::cout << "Course " << search << " has been found." << std::endl;
                    std::cout << "Course Name: " << match->getCourseName() << std::endl;
                    
                    std::cout << "Enter Section Name (0 to exit): ";
                    std::string sectionName;
                    std::getline(std::cin, sectionName);

                    if (sectionName == "0") break;
                    
                    db.createSection(courseID, sectionName);
        
                    std::cout << std::endl;
                    std::cout << "Course has been created." << std::endl;
                    consolePause();
                    break;
                } while (true);
                break;
            }
            case 6: //Add Faculty to Section
            {
                //Check if section exists
                int sectionID, facultyID;
                std::cout << "Enter Section ID to add faculty to: ";
                std::cin >> sectionID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Section* section = db.findSectionByID(sectionID);
                if (section) {
                    std::cout << std::endl;
                    std::cout << "Section " << sectionID << " has been found." << std::endl;
                    std::cout << "Section Name: " << section->getSectionName() << std::endl;
                    std::cout << std::endl;
                    std::cout << "Enter the faculty ID to assign to the section: ";
                    std::cin >> facultyID;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Faculty* user = db.findFacultyByID(facultyID);
                    if (user) {
                        std::cout << std::endl;
                        std::cout << "Faculty " << facultyID << " has been found." << std::endl;
                        std::cout << "Faculty Name: " << user->getFullName() << std::endl;
                        std::cout << std::endl;
                        std::cout << "Are you sure you want to add this faculty? (Y/N): ";
                        std::string confirm;
                        std::cin >> confirm;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (confirm == "y" || confirm == "Y") {
                            db.addFacultyToSection(*section, *user);
                        } else {
                            std::cout << "Cancelled adding faculty to section." << std::endl;
                        }
                        consolePause();
                        break;
                    } else {
                        std::cout << std::endl;
                        std::cerr << "No faculty with the inputted ID has been found." << std::endl;
                        consolePause();
                        continue;
                    }
                    consolePause();
                    break;
                } else {
                    std::cout << std::endl;
                    std::cerr << "No section with the inputted ID has been found." << std::endl;
                    consolePause();
                    continue;
                }
            
                break;
            }
            case 7: //Add Student to Section
            {
                //Check if section exists
                int sectionID, studentID;
                std::cout << "Enter Section ID to enroll student to: ";
                std::cin >> sectionID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Section* section = db.findSectionByID(sectionID);
                if (section) {
                    std::cout << std::endl;
                    std::cout << "Section " << sectionID << " has been found." << std::endl;
                    std::cout << "Section Name: " << section->getSectionName() << std::endl;
                    std::cout << std::endl;
                    std::cout << "Enter the student ID to add to the section: ";
                    std::cin >> studentID;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Student* user = db.findStudentByID(studentID);
                    if (user) {
                        std::cout << std::endl;
                        std::cout << "Student " << studentID << " has been found." << std::endl;
                        std::cout << "Student Name: " << user->getFullName() << std::endl;
                        std::cout << std::endl;
                        std::cout << "Are you sure you want to enroll this student? (Y/N): ";
                        std::string confirm;
                        std::cin >> confirm;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (confirm == "y" || confirm == "Y") {
                            db.addStudentToSection(*section, *user);
                        } else {
                            std::cout << "Cancelled adding faculty to section." << std::endl;
                        }
                        consolePause();
                        break;
                    } else {
                        std::cout << std::endl;
                        std::cerr << "No faculty with the inputted ID has been found." << std::endl;
                        consolePause();
                        continue;
                    }
                    consolePause();
                    break;
                } else {
                    std::cout << std::endl;
                    std::cerr << "No section with the inputted ID has been found." << std::endl;
                    consolePause();
                    continue;
                }
            
                break;
            }
            case 8: // Logout
                break;
            default:
                std::cerr << "\033[1;31m"
                          << "Invalid choice. Please try again." << std::endl
                          << "\033[0m";
        }
    }
}

void menuCreateUser() {
    std::string type = "";
    
    int choice = 0;
    while ( choice != 5 ) {
        consoleClear();
        std::cout << "\033[1;32m";
        std::cout << "==============================" << std::endl;
        std::cout << "|         CREATE USER        |" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "\033[0m";
        std::cout << std::endl;
        std::cout << "Select the type of user to create: " << std::endl;
        std::cout << std::endl;
        
        std::cout << "1. Student" << std::endl;
        std::cout << "2. Faculty" << std::endl;
        std::cout << "3. Staff" << std::endl;
        std::cout << "4. Admin" << std::endl;
        std::cout << "5. Back to Admin Menu" << std::endl;
        
        std::cout << std::endl;
        std::cout << "\033[1;34m"
                  << "Enter your choice: "
                  << "\033[0m";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl;

        switch (choice) {
            case 1: // Student
                std::cout << "Selected Student" << std::endl;
                type = "Student";
                break;
            case 2: // Faculty
                std::cout << "Selected Faculty" << std::endl;
                type = "Faculty";
                break;
            case 3: // Staff
                std::cout << "Selected Staff" << std::endl;
                type = "Staff";
                break;
            case 4: // Admin
                std::cout << "Selected Admin" << std::endl;
                type = "Admin";
                break;
            case 5: // Back to Admin Menu
                break;
            default:
                std::cerr << "\033[1;31m"
                          << "Invalid choice. Please try again." << std::endl
                          << "\033[0m";
        }

        std::string dataDir = "data/";
        if (choice == 5) {
            break;
        } else if ( type == "Student" || type == "Faculty" || type == "Staff" ) {
            std::string fname;
            std::string mname;
            std::string lname;
            
            std::cout << "Enter First Name:  ";
            std::getline(std::cin, fname);
            std::cout << "Enter Middle Name: ";
            std::getline(std::cin, mname);
            std::cout << "Enter Last Name:   ";
            std::getline(std::cin, lname);

            if (type == "Student") {
                db.createStudent(fname, mname, lname);
            } else if (type == "Faculty") {
                db.createFaculty(fname, mname, lname);
            } else if (type == "Staff") {
                db.createStaff(fname, mname, lname);
            }
            
        } else if (type == "Admin") {
            std::string email;
            std::string password;
            
            std::cout << "Enter Email:    ";
            std::getline(std::cin, email);
            std::cout << "Enter Password: ";
            std::getline(std::cin, password);

            db.createAdmin(email, password);
        }

        std::cout << std::endl;
        std::cout << "User has been created." << std::endl;
        consolePause();
    }
}

void consoleClear() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For POSIX systems
#endif
}

void consolePause() {
#ifdef _WIN32
    std::cout << std::endl;
    std::cout << "Press any key to continue...";
    system("pause");
#else
    std::cout << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
#endif
}