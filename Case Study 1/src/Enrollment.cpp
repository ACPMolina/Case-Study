//
// Created by twenty on 9/17/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include "User.h"
#include "Student.h"

using namespace std;

class Student {
public:
    string fname, mname, lname, program;
    int age, yearlvl;
    int studentId;

    Student(string _fname, string _mname, string _lname, int _age, int _yearlvl, string _program)
        : fname(_fname), mname(_mname), lname(_lname), age(_age), yearlvl(_yearlvl), program(_program) {
    }

    int getStudentId() const {
        return studentId;
    }

    void setStudentId(int id) {
        studentId = id;
    }
};

class StudentDatabase {
private:
    vector<Student> students;
    int lastAssignedNumber;

public:
    StudentDatabase() : lastAssignedNumber(0) {}

    void addStudent(string fname, string mname, string lname, int age, int yearlvl, string program) {
        int nextStudentId = getCurrentYear() * 100000 + (lastAssignedNumber + 1) ;
        students.emplace_back(fname, mname, lname, age, yearlvl, program);
        students.back().setStudentId(nextStudentId);
        cout << "Student enrolled successfully!\n\n";
        lastAssignedNumber = lastAssignedNumber + 1; //increments every after entry
    }

    int getLastAssignedNumber() const {
        return lastAssignedNumber;
    }

    void listStudents() {
        cout << "List of Students:" << endl;
        for (const Student& student : students) {
            cout << "\nStudent ID: " << student.getStudentId();
            cout << "\nName: " << student.fname;
				if (student.mname == " " || student.mname == ""){
					cout << " ";
				}
				else {
					cout << " " << student.mname << " ";
				}
			cout << student.lname;
            cout << "\nAge: " << student.age;
            cout << "\nYear Level: " << student.yearlvl << (student.yearlvl == 1 ? "st" : student.yearlvl == 2 ? "nd" : student.yearlvl == 3 ? "rd" : "th") << " Year";
            cout << "\nProgram: " << student.program << endl << endl;
        }
    }

    void saveStudentData(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        for (const Student& student : students) {
            file << student.getStudentId() << "," << student.fname << "," << student.mname << "," << student.lname << ","
                 << student.age << "," << student.yearlvl << "," << student.program << "\n";
        }
        file.close();
        cout << "\n\nData saved successfully." << endl;
    }

    void loadStudentData(const string& filename) {
        students.clear();
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int studentId, age, yearlvl;
            string fname, mname, lname, program;

            if (ss >> studentId && ss.ignore() && getline(ss, fname, ',') && getline(ss, mname, ',') &&
                getline(ss, lname, ',') && ss >> age && ss.ignore() && ss >> yearlvl && ss.ignore() &&
                getline(ss, program)) {
                students.emplace_back(fname, mname, lname, age, yearlvl, program);
                students.back().setStudentId(studentId);
                lastAssignedNumber = studentId % 100000; // Update last assigned number
            } else {
                cout << "Error parsing line: " << line << endl;
            }
        }
        file.close();
        cout << "Data successfully loaded." << endl;
    }

    int getCurrentYear() {
        time_t now = time(0);
        tm* timeInfo = localtime(&now);
        return timeInfo->tm_year + 1900;
    }
};

int main() {
    StudentDatabase studentDB;
    string studentDataFile = "students.txt";

    studentDB.loadStudentData(studentDataFile);

    while (true) {
        cout << "Options:" << endl;
        cout << "1. Enroll" << endl;
        cout << "2. List of Students" << endl;
        cout << "3. Save and Quit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string fname, mname, lname, program;
                char conf;
                int age, yearlvl;
                system("cls");
                cout << "==================================================================\n";
                cout << "\t\t\tENROLL\n";
                cout << "==================================================================\n\n";
                int nextStudentId = studentDB.getCurrentYear() * 100000 + (studentDB.getLastAssignedNumber() + 1);
                cout << "Student ID: " << nextStudentId << endl;
                cout << "Enter first name: ";
                cin.ignore();
                getline(cin, fname);
                cout << "Enter middle name (press enter if not applicable): ";
                getline(cin, mname);
                cout << "Enter last name: ";
                getline(cin, lname);
                cout << "Enter age: ";
                cin >> age;
                cout << "Enter Year Level: ";
                cin >> yearlvl;
                cout << "Enter program: ";
                cin.ignore();
                getline(cin, program);

                cout << "\n\nEntered details: ";
                cout << "\nName: " << fname;
                if (mname == " " || mname == ""){
					cout << " ";
				}
				else {
					cout << " " << mname << " ";
				}
				cout << lname;
                cout << "\nAge: " << age;
                cout << "\nYear Level: " << yearlvl << (yearlvl == 1 ? "st" : yearlvl == 2 ? "nd" : yearlvl == 3 ? "rd" : "th") << " Year";
                cout << "\nProgram: " << program;
                cout << "\n\nPress Y if all details are correct. Press N if not: ";
                cin >> conf;
                if (conf == 'Y' || conf == 'y') {
                    studentDB.addStudent(fname, mname, lname, age, yearlvl, program);
                } else if (conf == 'N' || conf == 'n') {
                    cout << "Student enrollment cancelled.\n\n";
                }
                break;
            }
            case 2:
                system("cls");
                cout << "==================================================================\n";
                cout << "\t\t\tLIST OF STUDENTS\n";
                cout << "==================================================================\n\n";
                studentDB.listStudents();
                break;
            case 3:
                studentDB.saveStudentData(studentDataFile);
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

