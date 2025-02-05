#include "Entity.h"
#include "Transform.h"
#include "Renderer.h"

int main() {
    Entity player(1);

    Transform* transform = player.AddComponent<Transform>(10, 20);

    Transform* retrieved = player.GetComponent<Transform>();
    if (retrieved) {
        Vector2 pos = retrieved->GetPosition();
        std::cout << "Position: (" << pos.x << ", " << pos.y << ")\n";

        retrieved->SetPosition(30, 40);
        pos = retrieved->GetPosition();
        std::cout << "New Position: (" << pos.x << ", " << pos.y << ")\n";
    }

    player.AddComponent<Renderer>();

    player.Update();

    return 0;
}
