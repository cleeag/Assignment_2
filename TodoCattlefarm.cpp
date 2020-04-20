/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoCow.h"
#include <cstdlib>

// Cattlefarm cost 80 upgrade cost 16
// Cattlefarm size 6, 6
// Cattlefarm init max num. of employee is CATTLEFARM_MAX_NUM_EMPLOYEE_MIN
// Cattlefarm Upgrade:
//      level increases by 1;
//      max num. of employees increases by 1 until CATTLEFARM_MAX_NUM_EMPLOYEE_MAX
// Cattlefarm Makemoney:
//      min(num. of cows, num. of feeders in work) x level x 10;

const int CATTLEFARM_COST = 80;
const int CATTLEFARM_UPGRADE_COST = 16;
const int CATTLEFARM_SIZE_X = 6; const int CATTLEFARM_SIZE_Y = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MIN = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MAX = (CATTLEFARM_SIZE_X-2) * (CATTLEFARM_SIZE_Y-2);

// TODO: Start to implement your code.
Cattlefarm::Cattlefarm():Property(CATTLEFARM_COST, CATTLEFARM_UPGRADE_COST, CATTLEFARM_MAX_NUM_EMPLOYEE_MAX) {}
bool Cattlefarm::checkEmployee(Employee*) const{
}
void Cattlefarm::upgrade(){
    Property::upgrade();
}
int Cattlefarm::makeMoney() const {
    int num_cow = 0, feeders_at_work = 0;
    const Employee**  const_emp_list = new const Employee* [getNumEmployee()];
    getConstEmployeeList(const_emp_list);
    for (int i = 0; i < getNumEmployee(); ++i) {
        if (const_emp_list[i]->getName() == "Feeder" and const_emp_list[i]->getState() == ObjectState::WORK)
            feeders_at_work++;
        if (const_emp_list[i]->getName() == "Cow")
            num_cow++;
    }
    return min(num_cow , feeders_at_work) * getLevel() * 10 ;
}

void Cattlefarm::removeDiedCow() {
    const Employee**  const_emp_list = new const Employee* [getNumEmployee()];
    getConstEmployeeList(const_emp_list);
    for (int i = 0; i < getNumEmployee(); ++i) {
        if (const_emp_list[i]->getName() != "Cow" ) continue;
        Employee* tmp_e = const_cast<Employee*>(const_emp_list[i]);
        Cow* tmp_cow = dynamic_cast<Cow*>(tmp_e);
        if (!tmp_cow->isAlive()){
            fireEmployee(tmp_cow);
        }
    }
}

char Cattlefarm::getSymbol() const{
    return 'C';
}
string Cattlefarm::getName() const{
    return "Cattlefarm";
}