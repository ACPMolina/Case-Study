#ifndef USER_H
#define USER_H

#include "json.hpp"

#include <string>

class User {
public:
    // CONSTRUCTORS
    User(const std::string& email,
         const std::string& password);

    User(const std::string& fname,
         const std::string& mname,
         const std::string& lname);

    User(const std::string& email,
         const std::string& password,
         const std::string& fname,
         const std::string& mname,
         const std::string& lname);

    User() = default;

    // DECONSTRUCTOR
    virtual ~User() = default;

    // GETTER METHODS
    std::string getEmail() const;
    std::string getPassword() const;
    std::string getFName() const;
    std::string getMName() const;
    std::string getLName() const;
    std::string getFullName() const;
    virtual std::string getClassName() const;
    

    // SETTER METHOD
    void setPassword(const std::string& newPassword);

protected:
    std::string username;
    std::string email;
    std::string password;
    std::string fname;
    std::string mname;
    std::string lname;
};

#endif