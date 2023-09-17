//
// Created by twenty on 9/17/23.
//

#ifndef CASESTUDY1_STUDENT_H
#define CASESTUDY1_STUDENT_H
#include "User.h"
#include <vector>

class Student : public User {
private:
    int yearLevel;
    std::vector<int> grades;
};
#endif //CASESTUDY1_STUDENT_H

