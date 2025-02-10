#include "Entity.h"
#include <iostream>

Entity::~Entity() {
    for (auto& component : m_components) {
        delete this;
    }
    m_components.clear();
}

void Entity::Update() {
    for (auto& component : m_components) {
		this->Update();
    }
}
