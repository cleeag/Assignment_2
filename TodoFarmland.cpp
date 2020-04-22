/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "TodoFarmland.h"
#include "Employee.h"
#include <cstdlib>

// Farmland cost 50 upgrade cost 10
// Farmland size 5, 5
// Farmland init max num. of employee is FARMLAND_MAX_NUM_EMPLOYEE_MIN
// Farmland Upgrade:
//      level increases by 1;
//      max num. of employee increases by 1 until FARMLAND_MAX_NUM_EMPLOYEE_MAX
// Farmland Makemoney:
//      getRandInt(0, num. of employees in work x 2 + num. of farmers in work x 6 + level x 3)

const int FARMLAND_COST = 50;
const int FARMLAND_UPGRADE_COST = 10;
const int FARMLAND_SIZE_X = 5; const int FARMLAND_SIZE_Y = 5;
const int FARMLAND_MAX_NUM_EMPLOYEE_MIN = 3;
const int FARMLAND_MAX_NUM_EMPLOYEE_MAX = (FARMLAND_SIZE_X-2) * (FARMLAND_SIZE_Y-2);

#ifdef __HARVEST_MOON_DEBUG__
    inline void debug_getRandInt(string s) {cout << s << endl;};
#else
    inline void debug_getRandInt(string s) {};
#endif

//return random int in [low, high).
int getRandInt(int low, int high) {
    int res = rand() % high + low;
    debug_getRandInt("getRandInt: low is "+to_string(low));
    debug_getRandInt("getRandInt: high is "+to_string(high));
    debug_getRandInt("getRandInt: res is "+to_string(res));
    return res;
}

// TODO: Start to implement your code.
Farmland::Farmland(int x, int y):Property(FARMLAND_COST, FARMLAND_UPGRADE_COST, FARMLAND_MAX_NUM_EMPLOYEE_MIN) {
    setXY(x, y);
    setSize(FARMLAND_SIZE_X, FARMLAND_SIZE_Y);
}
bool Farmland::checkEmployee(Employee* emp) const{
    if (emp == nullptr) return false;
    if (emp->getName() == "Farmer" or emp->getName() == "Employee") return true;
    else return false;
}
void Farmland::upgrade(){
    if (getLevel() < FARMLAND_MAX_NUM_EMPLOYEE_MAX) {
        Property::upgrade();
        setMaxNumEmployee(getMaxNumEmployee() + 1);
    }
}
int Farmland::makeMoney() const {
    int emp_at_work = 0, farmers_at_work = 0;
    const Employee**  const_emp_list = new const Employee* [getNumEmployee()];
    getConstEmployeeList(const_emp_list);
    for (int i = 0; i < getNumEmployee(); ++i) {
        if (const_emp_list[i]->getName() == "Employee" and const_emp_list[i]->getState() == ObjectState::WORK)
            emp_at_work++;
        if (const_emp_list[i]->getName() == "Farmer" and const_emp_list[i]->getState() == ObjectState::WORK)
            farmers_at_work++;
    }
    return getRandInt(0, emp_at_work * 2 + farmers_at_work * 6 + getLevel() * 3);
}
char Farmland::getSymbol() const{
    return 'R';
}
string Farmland::getName() const{
    return "Farmland";
}