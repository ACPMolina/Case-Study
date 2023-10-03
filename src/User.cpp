#include "User.h"

// CONSTRUCTORS
User::User(const std::string& email,
           const std::string& password)
         : email(email),
           password(password) {}

User::User(const std::string& fname,
           const std::string& mname,
           const std::string& lname)
         : fname(fname),
           mname(mname),
           lname(lname) {}

User::User(const std::string& email,
           const std::string& password,
           const std::string& fname,
           const std::string& mname,
           const std::string& lname)
         : email(email),
           password(password),
           fname(fname),
           mname(mname),
           lname(lname) {}

// GETTER METHODS
std::string User::getEmail() const {
    return email;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getFName() const {
    return fname;
}

std::string User::getMName() const {
    return mname;
}

std::string User::getLName() const {
    return lname;
}

std::string User::getFullName() const {
    return (lname + ", " + fname + " " + mname);
}

std::string User::getClassName() const {
    return "User";
}

// SETTER METHOD
void User::setPassword(const std::string& newPassword) {
    password = newPassword;
}