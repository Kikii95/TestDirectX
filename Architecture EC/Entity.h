#pragma once
#include <map>
#include <typeindex>
#include "Component.h"

class Entity {
private:
    int m_id;
    std::map<std::type_index, Component*> m_components;

public:
    Entity(int id) : m_id(id) {}
    ~Entity();

    int GetID() const { return m_id; }

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args);

    template <typename T>
    T* GetComponent();

    template <typename T>
    void RemoveComponent();

    void Update();

};

#include "Entity.inl"