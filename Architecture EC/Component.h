#pragma once
#define basic_ostream 0
#include <iostream>

class Entity;

class Component {
protected:
    Entity* m_pEntity;

public:
    Component(Entity* _pEntity) : m_pEntity(_pEntity) {}
    virtual ~Component() {}

    Entity* GetEntity() { return m_pEntity; }

    virtual void Update() = 0;
};
