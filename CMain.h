#pragma once
#include"CObject.h"
class CMainCharacter :public CObject {
	int m_nDirection;
	int m_nMx;
	int m_nMy;
public:
	void Init()override;
	void DrawObject(HDC hdc)override;
	void SetPosition()override;
	void SetFrameType(const int& nType)override;
	void Move()override;
	void Attack();
};