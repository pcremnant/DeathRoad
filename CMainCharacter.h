#pragma once
#include"CObject.h"
#define MAXZ 1.4
#define MINZ 1.0
class CMainCharacter :public CObject {
	int m_nDirection;
	bool m_nClick;
public:
	void Init()override;
	void DrawObject(HDC hdc)override;
	void SetPosition()override;
	void SetFrameType(const int& nType)override;
	void Move()override;
	int Upgrade()override;
	int Attack()override;
	int Dead()override;
};