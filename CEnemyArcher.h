#pragma once
#include"CObject.h"

class CEnemyArcher : public CObject {
protected:

	int m_nSpeed;
	int m_nDeadTimer;
	int m_nReroad;
	int m_nCurrentReroad;
public:
	CEnemyArcher(CSoundManager* sound) : CObject(sound) {}
	virtual void Init() override = 0;
	void SetPosition() override final;
	void DrawObject(HDC hdc)override final;
	int Update() override final;
	void Move()override final;
	int Attack() override final;
	int Dead() override final;
	void SetFrameType(const int& nType) override final;

	void GetUpgrade()override final {};
};