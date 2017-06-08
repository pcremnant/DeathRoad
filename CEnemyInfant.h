#pragma once
#include"CObject.h"

class CEnemyInfant : public CObject {
	int m_nSpeed;
	int m_nDeadTimer;
public:
	void Init() override;
	void SetPosition() override;
	void DrawObject(HDC hdc)override;
	void Move()override;
	void SetFrameType(const int& nType) override;
	void GetUpgrade()override {};
};