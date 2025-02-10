#include <iostream>
#include "Entity.h"
#include "Transform.h"

int main() {
    Entity player(1);
    std::cout << "Entity ID: " << player.GetID() << std::endl;

    Transform* transform = player.AddComponent<Transform>();
    if (transform) {
        std::cout << "Transform ajouté avec ID: " << transform->GetID() << std::endl;
    }
    else {
        std::cout << "Échec de l'ajout du Transform." << std::endl;
        return 1;
    }

    std::cout << "Rotation initiale :" << std::endl;
    transform->PrintRotation();

    std::cout << "Rotation de 90 degrés autour de l'axe Y..." << std::endl;
    transform->RotateYaw(DirectX::XMConvertToRadians(90));
    transform->UpdateMatrix(); 

    std::cout << "Rotation après transformation :" << std::endl;
    transform->PrintRotation();

    player.RemoveComponent<Transform>();
    if (!player.GetComponent<Transform>()) {
        std::cout << "Transform supprimé avec succès." << std::endl;
    }
    else {
        std::cout << "Échec de la suppression du Transform." << std::endl;
    }

    return 0;
}
