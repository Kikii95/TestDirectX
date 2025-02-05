#pragma once
#include "Component.h"

struct Vector2 { float x, y; };

class Transform : public Component {
private:
    Vector2 position;

public:
    Transform(Entity* entity, float x = 0, float y = 0)
        : Component(entity), position{ x, y } {}

    void SetPosition(float x, float y) { position = { x, y }; }
    Vector2 GetPosition() { return position; }

    void Update() override {
       /* std::cout << "Transform Update: (" << position.x << ", " << position.y << ")\n";*/
    }
};
