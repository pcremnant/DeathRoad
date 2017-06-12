#pragma once
#include"CItem.h"
#include"CCastle.h"
class CArrow :public CItem {
	CVector3D m_nCoorinate;
	CVector3D m_nDirection_Vector;
	float m_nAngle;
	int m_nCross;
	int m_nPower;
	int m_nFy;
	bool Click;
public:
	void Ready(int, int,bool,RECT);
	void DrawItem(HDC hdc)override;
	void Init()override;
	void Move();
};