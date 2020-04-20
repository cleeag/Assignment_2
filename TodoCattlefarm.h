/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#ifndef CATTLEFARM_H_
#define CATTLEFARM_H_

#include "Property.h"
extern const int CATTLEFARM_SIZE_X;
extern const int CATTLEFARM_SIZE_Y;

// HINT: You may seek help from Property::fireEmployee()
//       when you implement your Cattlefarm::removeDiedCow().
// TODO: Start to implement your code.
class Cattlefarm: public Property{
public:
    Cattlefarm(int, int);
    bool checkEmployee(Employee*) const;
    void upgrade();
    int makeMoney() const;
    void removeDiedCow();
    char getSymbol() const;
    string getName() const;
};
#endif /*CATTLEFARM_H_*/