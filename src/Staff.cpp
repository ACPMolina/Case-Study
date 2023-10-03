#include "Staff.h"

#include <algorithm>

// CONSTRUCTORS
Staff::Staff(const std::string& email,
             const std::string& password,
             const std::string& fname,
             const std::string& mname,
             const std::string& lname,
             int staffID)
           : User(email, password, fname, mname, lname),
             staffID(staffID) {}

// GETTER METHODS
int Staff::getStaffID() const {
    return staffID;
}

std::string Staff::getClassName() const {
    return "Staff";
}

bool Staff::operator==(const Staff &compare) const{
  return staffID == compare.staffID;
}