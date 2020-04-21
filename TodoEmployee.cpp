/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "Employee.h"

// Employee cost 5 salary 1.
// Employee 1 day work & 1 day rest.
const int EMPLOYEE_COST = 5;
const int EMPLOYEE_SALARY = 1; // Get paied when in both work and rest states.
const int EMPLOYEE_NUM_WORK_DAYS = 1;
const int EMPLOYEE_NUM_REST_DAYS = 1;
// All types of Employees have size 1.
const int ALLEMPLOYEE_SIZE_X = 1;
const int ALLEMPLOYEE_SIZE_Y = 1;

Employee::Employee()
        : Employee(EMPLOYEE_COST, EMPLOYEE_SALARY, EMPLOYEE_NUM_WORK_DAYS, EMPLOYEE_NUM_REST_DAYS) {
}

Employee::Employee(int cost, int salary, int ndays_work, int ndays_rest)
        : m_cost(cost), m_salary(salary), m_ndays_work(ndays_work), m_ndays_rest(ndays_rest) {
    setSize(ALLEMPLOYEE_SIZE_X, ALLEMPLOYEE_SIZE_Y);
}

Employee::~Employee() {
    //Auto-generated destructor stub
}

void Employee::writeToStream(ostream &os) const {
    Object::writeToStream(os);
    os << "Work Age: " << getWorkAge() << endl;
    os << "Salary: " << getSalary() << endl;
}

// TODO: Start to implement your code.

//Return the cost of the employee.
int Employee::getCost() const {
    return m_cost;
}


//Return the number of work days of the employee.
int Employee::getNumWorkDays() const {
    return m_ndays_work;
}

//Return the number of rest days of the employee.
int Employee::getNumRestDays() const {
    return m_ndays_rest;
}

//Return the work age of the employee.
int Employee::getWorkAge() const {
    return m_work_age;
}

//Return the salary according to the specification.
int Employee::getSalary() const {
    return m_salary;
}

//Update the state: Work/Rest according to the m_work_age and the specification
//If the employee has not been assigned to a property,
//Its state is always NORMAL.
//If the employee has been assigned.
//Its state changes between WORK(first)/REST.
void Employee::updateState() {
    int work_age = getWorkAge();
    int full_cycle = getNumRestDays() + getNumWorkDays();

    if (work_age == 0) {
        setState(ObjectState::WORK);
    } else if(work_age % full_cycle == full_cycle - 1){
        setState(ObjectState::REST);
    } else if (work_age % full_cycle == 0){
        setState(ObjectState::WORK);
    }

//    if (work_age == 0) {
//        setState(ObjectState::WORK);
//    } else if (getName() == "Employee") {
//        if (work_age % 2 == 1) {
//            setState(ObjectState::REST);
//        } else if (work_age % 2 == 0) {
//            setState(ObjectState::WORK);
//        }
//    } else if (getName() == "Farmer") {
//        if (work_age % 4 == 3) {
//            setState(ObjectState::REST);
//        } else if (work_age % 4 == 0) {
//            setState(ObjectState::WORK);
//        }
//    } else if (getName() == "Feeder") {
//        if (work_age % 7 == 6) {
//            setState(ObjectState::REST);
//        } else if (work_age % 7 == 0) {
//            setState(ObjectState::WORK);
//        }
//    } else if (getName() == "Cow") {
//        if (work_age % 2 == 1) {
//            setState(ObjectState::REST);
//        } else if (work_age % 2 == 0) {
//            setState(ObjectState::WORK);
//        }
//    }

}

//Increase the workage by one
void Employee::updateWorkAge() {
    m_work_age += 1;
}

//return the "Employee"
string Employee::getName() const {
    return "Employee";
}

//return the "e" (Captain Sensitive)
char Employee::getSymbol() const {
    return 'e';
}