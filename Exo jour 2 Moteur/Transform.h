#pragma once
#include <vector>
#include "Component.h"
#include <DirectXMath.h>
#include "Entity.h"
#include <DirectXPackedVector.h>

class Transform : public Component {
private:
    int m_id;

public:
    DirectX::XMFLOAT3 vSca;
    DirectX::XMFLOAT3 vDir;
    DirectX::XMFLOAT3 vUp;
    DirectX::XMFLOAT3 vRight;
    DirectX::XMFLOAT4 qRot;
    DirectX::XMFLOAT4X4 mRot;
    DirectX::XMFLOAT3 vPos;
    DirectX::XMFLOAT4X4 matrix;

	Transform(Entity* entity);
    ~Transform();

    int GetID() const;
    void Update() override;

    void Identity();
    void FromMatrix(DirectX::XMFLOAT4X4* matrix);
    void UpdateRotationFromVector();
    void UpdateRotationFromQuaternion();
    void UpdateRotationFromMatrix();
    void UpdateMatrix();
    void Rotate(float yaw, float pitch, float roll);

    void RotateYaw(float angle);
    void RotatePitch(float angle);
    void RotateRoll(float angle);
    void RotateWorld(DirectX::XMFLOAT4* pMatrix);
    void RotateWorldX(float angle);
    void RotateWorldY(float angle);
    void RotateWorldZ(float angle);

    void PrintRotation() const;

};

