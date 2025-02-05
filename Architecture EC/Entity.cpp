#include "Entity.h"
#include <iostream>

Entity::~Entity() {
    for (auto& pair : m_components) {
        delete pair.second;
    }
    m_components.clear();
}

void Entity::Update() {
    for (auto& pair : m_components) {
        pair.second->Update();
    }
}
