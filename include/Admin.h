#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

#include "json.hpp"

#include <string>

class Admin : public User {
public:
    // CONSTRUCTOR
    Admin(const std::string& email,
          const std::string& password,
          int adminID);
    
    Admin() = default;
    
    // SETTER METHODS
    int getAdminID() const;
    std::string getClassName() const;
    
    bool operator==(const Admin &compare) const;
    
private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Admin, email, password, adminID);
    
    int adminID;
};

#endif