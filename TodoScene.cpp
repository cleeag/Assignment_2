/*
 * File Created: Mon Mar 16 2020
 * Author:
 * SID:
*/

#include "Scene.h"
#include "Property.h"
#include "TodoFarmland.h"
#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoFarmer.h"
#include "TodoFeeder.h"
#include "TodoCow.h"

const int SCENE_W = 45;
const int SCENE_H = 10;
const int PROPERTY_X = 35;
const int SCENE_INIT_MONEY = 200;

Scene::Scene()
        : m_objects(nullptr), m_num_objects(0), m_money(SCENE_INIT_MONEY) {
    nextRound();
}

Scene::~Scene() {
    //shallowremove employees
    for (int i = m_num_objects - 1; i >= 0; i--) {
        if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE)
            shallowRemoveEmployee(dynamic_cast<Employee *>(m_objects[i]));
    }
    // remove properties
    for (int i = m_num_objects - 1; i >= 0; i--) {
        if (m_objects[i]->getObjectType() == ObjectType::PROPERTY)
            delete m_objects[i];
    }
    delete[] m_objects;
}

void Scene::shallowRemoveEmployee(Employee *e) {
    if (m_num_objects <= 0) return;
    if (m_num_objects == 1 && e == m_objects[0]) {
        m_num_objects = 0;
        m_objects = nullptr;
        return;
    }
    int i;
    for (i = 0; i < m_num_objects; i++) {
        if (m_objects[i] == e)
            break;
    }
    Object **newObjects = new Object *[m_num_objects--];
    for (int j = 0; j < m_num_objects; j++)
        newObjects[j] = m_objects[j];
    if (m_num_objects != i)
        newObjects[i] = m_objects[m_num_objects];
    delete[] m_objects;
    m_objects = newObjects;
}

bool Scene::checkOverlap(const Property *newproperty) {
    int x, y, sz_x, sz_y;
    newproperty->getXY(x, y);
    newproperty->getSize(sz_x, sz_y);
    for (int xx = x; xx < x + sz_x; xx++)
        for (int yy = y; yy < y + sz_y; yy++)
            if (getObjectAt(xx, yy) != nullptr) return true;
    return false;
}


void Scene::addProperty(int property, int x, int y) {
    Property *newProperty = nullptr;
    switch (property) {
        case FARMLAND:
            newProperty = new Farmland(x, y);
            break;
        case CATTLEFARM:
            newProperty = new Cattlefarm(x, y);
            break;
    }
    if (newProperty == nullptr) return;
    if (newProperty->getCost() > m_money || checkOverlap(newProperty)) {
        delete newProperty;
        return;
    }
    addObject(newProperty);
    m_money -= newProperty->getCost();
}


bool Scene::hire(Property *p, int employee) {
    Employee *newEmployee = nullptr;
    switch (employee) {
        case EMPLOYEE:
            newEmployee = new Employee();
            break;
        case FARMER:
            newEmployee = new Farmer();
            break;
        case FEEDER:
            newEmployee = new Feeder();
            break;
        case COW:
            newEmployee = new Cow();
            break;
    }
    if (newEmployee == nullptr) return false;
    if (newEmployee->getCost() > m_money || !p->assignEmployee(newEmployee)) {
        delete newEmployee;
        return false;
    }
    addObject(newEmployee);
    m_money -= newEmployee->getCost();
    return true;
}


Object *Scene::getObjectAt(int s_x, int s_y) const {
    int x, y, sz_x, sz_y;
    // If employee is at s_x, s_y, get employee
    // else, get property
    // otherwise return null
    for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::PROPERTY)
            continue;
        m_objects[i]->getXY(x, y);
        m_objects[i]->getSize(sz_x, sz_y);
        if (s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
            return m_objects[i];
    }
    for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE)
            continue;
        m_objects[i]->getXY(x, y);
        m_objects[i]->getSize(sz_x, sz_y);
        if (s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
            return m_objects[i];
    }
    return nullptr;
}

//perform shallow copying
void Scene::addObject(Object *newobj) {
    Object **newobjects = new Object *[m_num_objects + 1];
    for (int i = 0; i < m_num_objects; i++)
        newobjects[i] = m_objects[i];
    newobjects[m_num_objects++] = newobj;
    if (m_num_objects != 1)
        delete[] m_objects;
    m_objects = newobjects;
}

void Scene::getConstObjects(const Object **&obj, int &count) const {
    count = m_num_objects;
    if (m_num_objects == 0) {
        obj = nullptr;
        return;
    }
    obj = new const Object *[m_num_objects];
    for (int i = 0; i < m_num_objects; i++)
        obj[i] = m_objects[i];
}

// TODO: Start to implement your code.
bool Scene::isGameOver() const {
    return getMoney() < 0;
}

void Scene::removeProperty(Property *p) {
    int delete_amount = 1 + p->getNumEmployee();
    Object **newobjects = new Object *[m_num_objects - delete_amount];
    for (int new_i = 0, old_i = 0; new_i < m_num_objects - delete_amount;) {
        bool in_p = false;
        for (int i = 0; i < p->getNumEmployee(); ++i) {
            if (m_objects[old_i] == p) in_p = true;
        }
        if (m_objects[old_i] == p or in_p) {
            old_i++;
        } else {
            newobjects[new_i] = m_objects[old_i];
            new_i++;
            old_i++;
        }
    }
    delete p;
    delete[] m_objects;
    m_objects = newobjects;
    m_num_objects -= delete_amount;
}

// Operations to finish this round before entering the next round.
// - Make money
// - Compute salary
// - Update employee work age
// - Update employee status
// - Remove died cows
void Scene::nextRound() {
    Cow** dead_cows = new Cow* [m_num_objects];
    int dead_cow_num = 0;
    for (int i = 0; i < m_num_objects; ++i) {
        if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE) {
            if (m_objects[i]->getName() == "Employee") {
                m_money -= 1;
            } else if (m_objects[i]->getName() == "Farmer") {
                m_money -= 2;
            } else if (m_objects[i]->getName() == "Feeder") {
                m_money -= 5;
            } else if (m_objects[i]->getName() == "Cow") {
                Cow *cow = dynamic_cast<Cow *>(m_objects[i]);
                if (!cow->isAlive()){
                    dead_cows[dead_cow_num] = cow;
                    dead_cow_num += 1;
                }
            }
        }
    }
    for (int k = 0; k < dead_cow_num; ++k) shallowRemoveEmployee(dead_cows[k]);
    delete [] dead_cows;

    for (int j = 0; j < m_num_objects; ++j) {
        if (m_objects[j]->getObjectType() == ObjectType::PROPERTY) {
            if (m_objects[j]->getName() == "Cattlefarm") {
                dynamic_cast<Cattlefarm *>(m_objects[j])->removeDiedCow();
            }
            m_money += dynamic_cast<Property *>(m_objects[j])->makeMoney();
        }
    }
    for (int l = 0; l < m_num_objects; ++l) {
        if (m_objects[l]->getObjectType() == ObjectType::EMPLOYEE){
            dynamic_cast<Employee *>(m_objects[l])->updateState();
            dynamic_cast<Employee *>(m_objects[l])->updateWorkAge();
        }
    }
}

bool Scene::upgrade(Property *p) {
    if (p == nullptr) return false;
    if (p->getName() == "Farmland") dynamic_cast<Farmland * >(p)->upgrade();
    else if (p->getName() == "Cattlefarm") dynamic_cast<Cattlefarm * >(p)->upgrade();
}

bool Scene::fire(Employee *fired_emp) {
    if (fired_emp == nullptr) return false;

    Object **newobjects = new Object *[m_num_objects - 1];
    Property *tmp_property;
    Property *property_with_fired_emp = nullptr;
    for (int new_i = 0, old_i = 0; old_i < m_num_objects;) {
        if (m_objects[old_i]->getObjectType() == ObjectType::PROPERTY) {
            tmp_property = dynamic_cast<Property *>(m_objects[old_i]);
            const Employee **tmp_emp_list;
            tmp_property->getConstEmployeeList(tmp_emp_list);
            for (int i = 0; i < tmp_property->getNumEmployee(); ++i) {
                if (fired_emp == tmp_emp_list[i])
                    property_with_fired_emp = tmp_property;
            }
            delete [] tmp_emp_list;
        }
        if (m_objects[old_i] == fired_emp) {
            old_i++;
        } else {
            newobjects[new_i] = m_objects[old_i];
            new_i++;
            old_i++;
        }
    }
    if (property_with_fired_emp != nullptr) {
        property_with_fired_emp->fireEmployee(fired_emp);
        delete[] m_objects;
        m_objects = newobjects;
        m_num_objects -= 1;
    }
}


