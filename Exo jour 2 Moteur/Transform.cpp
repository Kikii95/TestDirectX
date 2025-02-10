#include "Transform.h"
#include <DirectXMath.h>

using namespace DirectX;

Transform::Transform(Entity* entity) : Component(entity) {
	Identity();
}

Transform::~Transform() {
}

int Transform::GetID() const {
    return m_pEntity->GetID();
}

void Transform::Update() {
    UpdateMatrix();
}

void Transform::Identity() {
    vSca = XMFLOAT3(1, 1, 1);
    vDir = XMFLOAT3(0, 0, 1);
    vUp = XMFLOAT3(0, 1, 0);
    vRight = XMFLOAT3(1, 0, 0);
    qRot = XMFLOAT4(0, 0, 0, 1);
    vPos = XMFLOAT3(0, 0, 0);
    XMStoreFloat4x4(&mRot, XMMatrixIdentity());
    XMStoreFloat4x4(&matrix, XMMatrixIdentity());
}

void Transform::FromMatrix(XMFLOAT4X4* matrix) {
    XMStoreFloat4x4(matrix, XMLoadFloat4x4(matrix));
}

void Transform::UpdateRotationFromVector() {
    XMStoreFloat4x4(&mRot, XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&vDir)));
}

void Transform::UpdateRotationFromQuaternion() {
    XMStoreFloat4x4(&mRot, XMMatrixRotationQuaternion(XMLoadFloat4(&qRot)));
}

void Transform::UpdateRotationFromMatrix() {
    XMStoreFloat4x4(&mRot, XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&vDir)));
}

void Transform::UpdateMatrix() {
    XMMATRIX mRot = XMMatrixRotationQuaternion(XMLoadFloat4(&qRot));
    XMMATRIX mScale = XMMatrixScalingFromVector(XMLoadFloat3(&vSca));
    XMMATRIX mTrans = XMMatrixTranslationFromVector(XMLoadFloat3(&vPos));
    XMMATRIX mWorld = mRot * mScale * mTrans;
    XMStoreFloat4x4(&matrix, mWorld);
}

void Transform::Rotate(float yaw, float pitch, float roll) {
    XMVECTOR qYaw = XMQuaternionRotationRollPitchYaw(0, yaw, 0);
    XMVECTOR qPitch = XMQuaternionRotationRollPitchYaw(pitch, 0, 0);
    XMVECTOR qRoll = XMQuaternionRotationRollPitchYaw(0, 0, roll);

    XMVECTOR qRotVector = XMLoadFloat4(&qRot);
    qRotVector = XMQuaternionMultiply(qRotVector, qYaw);
    qRotVector = XMQuaternionMultiply(qRotVector, qPitch);
    qRotVector = XMQuaternionMultiply(qRotVector, qRoll);

    XMStoreFloat4(&qRot, qRotVector);
}

void Transform::RotateYaw(float angle) {
    XMVECTOR rotationQuat = XMQuaternionRotationRollPitchYaw(0, angle, 0); 
    XMVECTOR currentQuat = XMLoadFloat4(&qRot);
    currentQuat = XMQuaternionMultiply(currentQuat, rotationQuat); 
    XMStoreFloat4(&qRot, currentQuat);
}

void Transform::RotatePitch(float angle) {
    XMVECTOR rotationQuat = XMQuaternionRotationRollPitchYaw(angle, 0, 0); 
    XMVECTOR currentQuat = XMLoadFloat4(&qRot);
    currentQuat = XMQuaternionMultiply(currentQuat, rotationQuat);
    XMStoreFloat4(&qRot, currentQuat);
}

void Transform::RotateRoll(float angle) {
    XMVECTOR rotationQuat = XMQuaternionRotationRollPitchYaw(0, 0, angle);
    XMVECTOR currentQuat = XMLoadFloat4(&qRot);
    currentQuat = XMQuaternionMultiply(currentQuat, rotationQuat);
    XMStoreFloat4(&qRot, currentQuat);
}

void Transform::RotateWorld(DirectX::XMFLOAT4* pMatrix) {
    XMMATRIX rotationMatrix = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4*>(pMatrix)); 
    XMVECTOR currentQuat = XMLoadFloat4(&qRot); 
    XMVECTOR rotationQuat = XMQuaternionRotationMatrix(rotationMatrix);
    currentQuat = XMQuaternionMultiply(currentQuat, rotationQuat);
    XMStoreFloat4(&qRot, currentQuat); 
}

void Transform::RotateWorldX(float angle) {
    XMVECTOR rotationAxis = XMVectorSet(1, 0, 0, 0);
    XMVECTOR rotationQuat = XMQuaternionRotationAxis(rotationAxis, angle); 
    XMVECTOR currentQuat = XMLoadFloat4(&qRot);
    currentQuat = XMQuaternionMultiply(currentQuat, rotationQuat);
    XMStoreFloat4(&qRot, currentQuat);
}

void Transform::RotateWorldY(float angle) {
    XMVECTOR rotationAxis = XMVectorSet(0, 1, 0, 0);
    XMVECTOR rotationQuat = XMQuaternionRotationAxis(rotationAxis, angle);
    XMVECTOR currentQuat = XMLoadFloat4(&qRot);
    currentQuat = XMQuaternionMultiply(currentQuat, rotationQuat);
    XMStoreFloat4(&qRot, currentQuat);
}

void Transform::RotateWorldZ(float angle) {
    XMVECTOR rotationAxis = XMVectorSet(0, 0, 1, 0); 
    XMVECTOR rotationQuat = XMQuaternionRotationAxis(rotationAxis, angle);
    XMVECTOR currentQuat = XMLoadFloat4(&qRot);
    currentQuat = XMQuaternionMultiply(currentQuat, rotationQuat);
    XMStoreFloat4(&qRot, currentQuat);
}

void Transform::PrintRotation() const {
    DirectX::XMVECTOR quaternion = XMLoadFloat4(&qRot);
    DirectX::XMVECTOR axis;
    float angle;

    DirectX::XMQuaternionToAxisAngle(&axis, &angle, quaternion);

    angle = DirectX::XMConvertToDegrees(angle);

    DirectX::XMFLOAT3 axisFloat;
    XMStoreFloat3(&axisFloat, axis);

    std::cout << "Rotation actuelle : Angle = " << angle
        << "° autour de l'axe (" << axisFloat.x
        << ", " << axisFloat.y
        << ", " << axisFloat.z << ")" << std::endl;
}
