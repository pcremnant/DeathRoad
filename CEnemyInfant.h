#pragma once
#include"CObject.h"

class CEnemyInfant : public CObject {
protected:

	int m_nSpeed;
	int m_nDeadTimer;
public:
	virtual void Init() override = 0;
	void SetPosition() override final;
	void DrawObject(HDC hdc)override final;
	void Move()override final;
	void SetFrameType(const int& nType) override final;
	void GetUpgrade()override final {};
};