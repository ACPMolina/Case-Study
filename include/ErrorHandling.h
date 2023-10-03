#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdexcept>
#include <string>

//Default Exception
class ProgramException : public std::exception {
public:
    // CONSTRUCTOR
    ProgramException(const char* message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class StudentNotFoundException : public ProgramException {
public:
    // CONSTRUCTOR
    StudentNotFoundException(const char* message) : ProgramException(message) {}
};

class FileNotFoundException : public ProgramException {
public:
    // CONSTRUCTOR
    FileNotFoundException(const char* message) : ProgramException(message) {}
};

class InvalidInputException : public ProgramException {
public:
    // CONSTRUCTOR
    InvalidInputException(const char* message) : ProgramException(message) {}
};

#endif