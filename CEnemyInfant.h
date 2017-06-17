#pragma once
#include"CObject.h"
#include"CCastle.h"

class CEnemyInfant : public CObject {
protected:

	int m_nSpeed;
	int m_nDeadTimer;
	CItem* m_pCastle{ nullptr };
public:
	CEnemyInfant(CSoundManager* sound, CItem* castle) : CObject(sound) {
		m_pCastle = castle;
	}
	virtual void Init() override = 0;
	void SetPosition() override final;
	void DrawObject(HDC hdc, bool bIntro = false)override final;
	int Update() override final;
	void Move()override final;
	int Attack() override final;
	int Dead() override final;
	void SetFrameType(const int& nType) override final;
	void GetUpgrade()override final {};
};