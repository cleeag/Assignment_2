/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "Property.h"
#include "Employee.h"

void Property::writeToStream(ostream& os) const {
	Object::writeToStream(os);
	os << "Cost:" << getCost() << endl;
    os << "Upgrade Cost:" << getUpgradeCost() << endl;
    os << "Level:" << getLevel() << endl;
    os << "# of Employee:" << getNumEmployee() << " / " << getMaxNumEmployee() << endl;
}

void Property::upgrade() {
    m_level++;
}

void Property::getConstEmployeeList(const Employee**& employee) const {
	if (m_num_employee == 0) {
		employee =nullptr;
		return;
	}
	employee = new const Employee*[m_num_employee];
	for (int i = 0; i < m_num_employee; i++)
		employee[i] = m_employee_list[i];
}

// TODO: Start to implement your code.

// The first parameter is the cost to build the property.
// The second parameter is the cost to upgrade the property.
// The third parameter is the max number of employees.
Property::Property(int m_cost, int m_upgrade_cost, int m_max_num_employee){
    this->m_cost = m_cost;
    this->m_upgrade_cost = m_upgrade_cost;
    this->m_max_num_employee = m_max_num_employee;
}

Property::~Property(){
    for (int i = 0; i < m_num_employee; ++i) {
        delete m_employee_list[i];
    }
}

// Return the building cost of the property.
int Property::getCost() const {
    return m_cost;
}

// Return the upgrade cost of the property.
int Property::getUpgradeCost() const{
    return m_upgrade_cost;
}

// Return the level of the property.
int Property::getLevel() const{
    return m_level;
}

// Return the number of the employees assigned to the property.
int Property::getNumEmployee() const{
    return m_num_employee;
}

// Return the max number of the employees.
int Property::getMaxNumEmployee() const{
    return m_max_num_employee;
}

// Set the max number of the employees.
void Property::setMaxNumEmployee(int m){
    m_max_num_employee = m;
}


// Assign an employee to the property.
// You should update the m_employee_list (with shallow copying), m_num_employee
// and set the x,y of Employee.
// All the employees should always be inside the range of their property.
// If the Property, e.g.Farmland(R), is at (0, 3) with size (5, 5),
// the first employee should at (1, 4);
// the second employee should at (1, 5);
//  012346x
// 3RRRRR
// 4R147R
// 5R258R
// 6R369R
// 7RRRRR
// y
// If reaches m_max_num_employee, it fails to assign.
// If the employee already in the list, it fails to assign.
// If the employee is unsuitable to the property, it fails to assign.
// Return true, if assign successfully.
// Otherwise, return false.
bool Property::assignEmployee(Employee*);

// Fire an employee.
// You should update the m_employee_list, m_num_employee
// and completely delete the employee.
// Assumption: You can assume the input parameter is in the m_employee_list if m_employee_list is not nullptr.
// Hint: You have to take care of the position of other employees after deleting one.
// Otherwise, it may cause a problem when you assigning new employees.
// Please note all the employees should always be inside their property.
// We gave some examples to clarify the "inside" and "outside" on the webpage.
// Return true, if assign successfully.
bool Property::fireEmployee(Employee*);


//return ObjectType::PROPERTY to identify that is an EMPLOYEE type.
virtual ObjectType getObjectType() const override {return ObjectType::PROPERTY;}