#pragma once
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

struct Transform
{
	XMFLOAT3 vSca;

	XMFLOAT3 vDir;
	XMFLOAT3 vUp;
	XMFLOAT3 vRight;

	XMFLOAT4 qRot;

	XMFLOAT4X4 mRot;

	XMFLOAT3 vPos;

	XMFLOAT4X4 matrix;

	Transform();
	~Transform();

	void Identity();
	void FromMatrix(XMFLOAT4X4* matrix);
	void UpdateRotationFromVector();
	void UpdateRotationFromQuaternion();
	void UpdateRotationFromMatrix();
	void UpdateMatrix();
	void Rotate(float yaw, float pitch, float roll);

	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void RotateRoll(float angle);

	void RotateWorld(XMFLOAT4* pMatrix);
	void RotateWorldX(float angle);
	void RotateWorldY(float angle);
	void RotateWorldZ(float angle);

};

