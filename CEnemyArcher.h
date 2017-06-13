#pragma once
#include"CObject.h"
#include"CCrossbowArrow.h"
#include"CEnemyArrowManager.h"
#include"CCastle.h"

class CEnemyArcher : public CObject {
protected:

	int m_nSpeed;
	int m_nDeadTimer;
	int m_nReroad;
	int m_nCurrentReroad;

	CEnemyArrowManager* m_pArrowManager{ nullptr };

	CItem* m_pCastle{ nullptr };
public:
	CEnemyArcher(CSoundManager* sound, CEnemyArrowManager* arrow, CItem* castle) : CObject(sound) {
		m_pCastle = castle;
		m_pArrowManager = arrow;
	}
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