#ifndef STAFF_H
#define STAFF_H

#include "User.h"
#include "Student.h"
#include "Section.h"
#include "json.hpp"

#include <string>
#include <vector>

class Staff : public User {
public:
    // CONSTRUCTOR
    Staff(const std::string& email,
            const std::string& password,
            const std::string& fname,
            const std::string& mname,
            const std::string& lname,
            int staffID);

    Staff() = default;

    // GETTER METHODS
    int getStaffID() const;
    std::string getClassName() const;

    bool operator==(const Staff &compare) const;

private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Staff, email, password, fname, mname, lname, staffID);
    
    int staffID;
};

#endif