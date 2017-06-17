#pragma once
#include"define.h"

class CVector3D {
	float x, y, z;
public:
	CVector3D() : x(0), y(0), z(0) {}
	CVector3D(const float& fx, const float& fy, const float& fz = 0) : x(fx), y(fy), z(fz) {}

	// CVector�� ���� �ִ� �� ����
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetZ() const { return z; }

	// CVector�� �� ����
	void SetX(const float fx) { x = fx; }
	void SetY(const float fy) { y = fy; }
	void SetZ(const float fz) { z = fz; }
	void SetPosition(const float& fx, const float& fy, const float& fz = 1)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	// �簢���� ������Ʈ �浹üũ
	bool ColisionBox(const int& szWidth, const int& szHeight, const RECT& rcOther)
	{
		// szWidth, szheight -> ȭ���� ���� ���� ����
		// rcOther�� �浹 üũ ����� ��ġ
		RECT rcTmp = { x - szWidth,y - szHeight,x + szWidth,y + szHeight };
		// �簢�� �浹 üũ
		if (PtInRect(&rcTmp, POINT{ rcOther.left,rcOther.top }))
			return true;
		else if (PtInRect(&rcTmp, POINT{ rcOther.right,rcOther.top }))
			return true;
		else if (PtInRect(&rcTmp, POINT{ rcOther.left,rcOther.bottom }))
			return true;
		else if (PtInRect(&rcTmp, POINT{ rcOther.right,rcOther.bottom }))
			return true;
		else if (PtInRect(&rcOther, POINT{ rcTmp.left,rcTmp.top }))
			return true;
		else if (PtInRect(&rcOther, POINT{ rcTmp.right,rcTmp.top }))
			return true;
		else if (PtInRect(&rcOther, POINT{ rcTmp.left,rcTmp.bottom }))
			return true;
		else if (PtInRect(&rcOther, POINT{ rcTmp.right,rcTmp.bottom }))
			return true;
		else if (rcOther.left <rcTmp.left && rcOther.right>rcTmp.right && rcOther.top < rcTmp.top && rcOther.bottom>rcTmp.bottom)
			return true;
		else if (rcTmp.left <rcOther.left && rcTmp.right>rcOther.right && rcTmp.top < rcOther.top && rcTmp.bottom>rcOther.bottom)
			return true;
		else
			return false;
	}

	// �̵� �Լ� -> ���ڸ� 2���� ������ z���� �ڵ����� 0�� ����.
	void Move(const float& x, const float& y, const float& z = 0)
	{
		this->x += x;
		this->y += y;
		this->z += z;
	}

	// �ڿ� true���� ������ z������ �����ش�.
	void Move(const CVector3D& vector, bool bZ = false)
	{
		if (bZ) {
			*this += vector;
		}
		else {
			this->Move(vector.x, vector.y);
		}
	}

	bool operator==(const CVector3D& other) const
	{
		if (this->x == other.x&&this->y == other.y&&this->z == other.z)
			return true;
		return false;
	}
	CVector3D operator=(const CVector3D& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}
	CVector3D operator+(const CVector3D& other) 
	{
		CVector3D vtTmp;
		vtTmp.x += other.x;
		vtTmp.y += other.y;
		vtTmp.z += other.z;
		return vtTmp;
	}
	CVector3D operator-(const CVector3D& other) 
	{
		CVector3D vtTmp;
		vtTmp.x -= other.x;
		vtTmp.y -= other.y;
		vtTmp.z -= other.z;
		return vtTmp;
	}
	void operator+=(const CVector3D& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
	}
	void operator-=(const CVector3D& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
	}
};