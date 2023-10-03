#include "Admin.h"

// CONSTRUCTOR
Admin::Admin(const std::string& email,
             const std::string& password,
             int adminID)
           : User(email, password),
             adminID(adminID) {}

// GETTER METHODS
int Admin::getAdminID() const {
    return adminID;
}

std::string Admin::getClassName() const {
    return "Admin";
}

bool Admin::operator==(const Admin &compare) const{
  return adminID == compare.adminID;
}
