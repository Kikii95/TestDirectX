#include "Transform.h"

using namespace DirectX;

Transform::Transform()
{
	Identity();
}

Transform::~Transform()
{
}

void Transform::Identity()
{
	vSca = XMFLOAT3(1, 1, 1);
	vDir = XMFLOAT3(0, 0, 1);
	vUp = XMFLOAT3(0, 1, 0);
	vRight = XMFLOAT3(1, 0, 0);
	qRot = XMFLOAT4(0, 0, 0, 1);
	vPos = XMFLOAT3(0, 0, 0);
	XMStoreFloat4x4(&mRot, XMMatrixIdentity());
	XMStoreFloat4x4(&matrix, XMMatrixIdentity());
}

void Transform::FromMatrix(XMFLOAT4X4* matrix)
{
	XMStoreFloat4x4(matrix, XMLoadFloat4x4(matrix));
}

void Transform::UpdateRotationFromVector()
{
	XMStoreFloat4x4(&mRot, XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&vDir)));
}

void Transform::UpdateRotationFromQuaternion()
{
	XMStoreFloat4x4(&mRot, XMMatrixRotationQuaternion(XMLoadFloat4(&qRot)));
}

void Transform::UpdateRotationFromMatrix()
{
	XMStoreFloat4x4(&mRot, XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&vDir)));
}

void Transform::UpdateMatrix() 
{
	XMMATRIX mRot = XMMatrixRotationQuaternion(XMLoadFloat4(&qRot));

	XMMATRIX mScale = XMMatrixScalingFromVector(XMLoadFloat3(&vSca));
	XMMATRIX mTrans = XMMatrixTranslationFromVector(XMLoadFloat3(&vPos));

	XMMATRIX mWorld = mRot * mScale * mTrans;
	XMStoreFloat4x4(&matrix, mWorld);
}

void Transform::Rotate(float yaw, float pitch, float roll) {
	XMVECTOR vYaw = XMVectorSet(0, yaw, 0, 0);
	XMVECTOR vPitch = XMVectorSet(pitch, 0, 0, 0);
	XMVECTOR vRoll = XMVectorSet(0, 0, roll, 0);

	XMVECTOR qYaw = XMQuaternionRotationRollPitchYawFromVector(vYaw);
	XMVECTOR qPitch = XMQuaternionRotationRollPitchYawFromVector(vPitch);
	XMVECTOR qRoll = XMQuaternionRotationRollPitchYawFromVector(vRoll);

	XMVECTOR qRot = XMLoadFloat4(&qRot);
	qRot = XMQuaternionMultiply(qRot, qYaw);
	qRot = XMQuaternionMultiply(qRot, qPitch);
	qRot = XMQuaternionMultiply(qRot, qRoll);

	XMStoreFloat4(&qRot, qRot);
}

void Transform::RotateYaw(float angle) {
	XMVECTOR vAngle = XMVectorSet(0, angle, 0, 0);
	XMVECTOR qAngle = XMQuaternionRotationRollPitchYawFromVector(vAngle);

	XMVECTOR qRot = XMLoadFloat4(&qRot);
	qRot = XMQuaternionMultiply(qRot, qAngle);

	XMStoreFloat4(&qRot, qRot);
}

void Transform::RotatePitch(float angle) {
	XMVECTOR vAngle = XMVectorSet(angle, 0, 0, 0);
	XMVECTOR qAngle = XMQuaternionRotationRollPitchYawFromVector(vAngle);

	XMVECTOR qRot = XMLoadFloat4(&qRot);
	qRot = XMQuaternionMultiply(qRot, qAngle);

	XMStoreFloat4(&qRot, qRot);
}

void Transform::RotateRoll(float angle) {
	XMVECTOR vAngle = XMVectorSet(0, 0, angle, 0);
	XMVECTOR qAngle = XMQuaternionRotationRollPitchYawFromVector(vAngle);

	XMVECTOR qRot = XMLoadFloat4(&qRot);
	qRot = XMQuaternionMultiply(qRot, qAngle);

	XMStoreFloat4(&qRot, qRot);
}