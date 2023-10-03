#include "Applicant.h"

// CONSTRUCTOR
Applicant::Applicant(const std::string& fname,
                     const std::string& mname,
                     const std::string& lname,
                     int applicantID,
                     std::vector<std::string> uploadedDocuments)
                   : User(fname, mname, lname),
                     applicantID(applicantID),
                     uploadedDocuments(uploadedDocuments) {}

// GETTER METHODS
int Applicant::getApplicantID() const {
    return applicantID;
};

std::string Applicant::getClassName() const {
    return "Applicant";
}

const std::vector<std::string>& Applicant::getUploadedDocuments() const {
    return uploadedDocuments;
}

// SETTER METHOD
void Applicant::setUploadedDocument(const std::string& newDocumentID) {
    uploadedDocuments.push_back(newDocumentID);
}

bool Applicant::operator==(const Applicant &compare) const{
  return applicantID == compare.applicantID;
}