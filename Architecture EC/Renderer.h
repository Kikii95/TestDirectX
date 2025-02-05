#pragma once
#include "Component.h"
#include "Entity.h"

class Renderer : public Component {
public:
    Renderer(Entity* entity) : Component(entity) {}

    void Update() override {
        std::cout << "Renderer: Dessiner l'entite " << GetEntity()->GetID() << "\n";
    }
};
