#pragma once
#include"define.h"

class CVector3D {
	float x, y, z;
public:
	CVector3D() : x(0), y(0), z(0) {}
	CVector3D(const float& fx, const float& fy, const float& fz = 0) : x(fx), y(fy), z(fz) {}

	// CVector가 갖고 있는 값 리턴
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetZ() const { return z; }

	// CVector에 값 세팅
	void SetX(const float fx) { x = fx; }
	void SetY(const float fy) { y = fy; }
	void SetZ(const float fz) { z = fz; }
	void SetPosition(const float& fx, const float& fy, const float& fz = 1)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	// 사각형과 오브젝트 충돌체크
	bool ColisionBox(const int& szWidth, const int& szHeight, const RECT& rcOther)
	{
		RECT rcTmp = { x - szWidth,y - szHeight,x + szWidth,y + szHeight };
		// 사각형 충돌 체크
		if (PtInRect(&rcTmp, POINT{ rcOther.left,rcOther.top }))
			return true;
		else if (PtInRect(&rcTmp, POINT{ rcOther.right,rcOther.top }))
			return true;
		else if (PtInRect(&rcTmp, POINT{ rcOther.left,rcOther.bottom }))
			return true;
		else if (PtInRect(&rcTmp, POINT{ rcOther.right,rcOther.bottom }))
			return true;
		else
			return false;
	}

	// 이동 함수 -> 인자를 2개만 넣으면 z에는 자동으로 0이 들어간다.
	void Move(const float& x, const float& y, const float& z = 0)
	{
		this->x += x;
		this->y += y;
		this->z += z;
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
	CVector3D operator+(const CVector3D& other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}
};