#include "Cam.h"

Cam::Cam()
{
	_pos = D3DXVECTOR3(0.0f, 11110.0f, 0.0f);
	_right = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_look = D3DXVECTOR3(10.0f, 10.0f, -1000.0f);
}

Cam::~Cam()
{

}

void Cam::getPosition(D3DXVECTOR3* pos)
{
	*pos = _pos;
}

void Cam::setPosition(D3DXVECTOR3* pos)
{
	_pos = *pos;
}

void Cam::getRight(D3DXVECTOR3* right)
{
	*right = _right;
}

void Cam::getUp(D3DXVECTOR3* up)
{
	*up = _up;
}

void Cam::getLook(D3DXVECTOR3* look)
{
	*look = _look;
}

void Cam::walk(float units)
{
	_pos += _look * units;
}

void Cam::strafe(float units)
{
	_pos += _right * units;
}

void Cam::fly(float units)
{
	_pos += _up * units;
}

void Cam::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_right, angle);

	// rotate _up and _look around _right vector
	D3DXVec3TransformCoord(&_up, &_up, &T);
	D3DXVec3TransformCoord(&_look, &_look, &T);
}

void Cam::yaw(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_up, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformCoord(&_right, &_right, &T);
	D3DXVec3TransformCoord(&_look, &_look, &T);
}

void Cam::roll(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_look, angle);

	// rotate _up and _right around _look vector
	D3DXVec3TransformCoord(&_right, &_right, &T);
	D3DXVec3TransformCoord(&_up, &_up, &T);
}

void Cam::getViewMatrix(D3DXMATRIX* V)
{
	// Keep Cam's axes orthogonal to each other
	D3DXVec3Normalize(&_look, &_look);

	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);

	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);

	// Build the view matrix:
	float x = -D3DXVec3Dot(&_right, &_pos);
	float y = -D3DXVec3Dot(&_up, &_pos);
	float z = -D3DXVec3Dot(&_look, &_pos);

	(*V)(0, 0) = _right.x; (*V)(0, 1) = _up.x; (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
	(*V)(1, 0) = _right.y; (*V)(1, 1) = _up.y; (*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
	(*V)(2, 0) = _right.z; (*V)(2, 1) = _up.z; (*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
	(*V)(3, 0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
}