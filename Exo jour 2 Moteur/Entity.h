#pragma once
#include "Component.h"
#include <vector>

class Entity {
private:
    int m_id;
	std::vector<Component*> m_components;

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