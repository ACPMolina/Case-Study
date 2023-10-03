#ifndef APPLICANT_H
#define APPLICANT_H

#include "User.h"

#include <string>

#include "json.hpp"

class Applicant : public User {
public:
    // CONSTRUCTOR
    Applicant(const std::string& fname,
              const std::string& mname,
              const std::string& lname,
              int applicantID,
              std::vector<std::string> uploadedDocuments);

    Applicant() = default;

    // GETTER METHODS
    int getApplicantID() const;
    std::string getClassName() const;
    const std::vector<std::string>& getUploadedDocuments() const;

    bool operator==(const Applicant &compare) const;

    // SETTER METHOD
    void setUploadedDocument(const std::string& newDocumentID);

private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Applicant, fname, mname, lname, applicantID, uploadedDocuments)
    
    int applicantID;
    std::vector<std::string> uploadedDocuments;
};

#endif