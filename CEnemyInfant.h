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
	int Update() override final;
	void Move()override final;
	int Attack() override final;
	void Dead() override final;
	void SetFrameType(const int& nType) override final;
	void GetUpgrade()override final {};
};