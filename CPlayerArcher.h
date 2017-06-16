#pragma once
#include"CObject.h"
#include"CPlayerArrowManager.h"

class CPlayerArcher : public CObject {
protected:

	int m_nReroad;
	int m_nCurrentReroad;

	CObject* m_pTarget{ nullptr };
	CPlayerArrowManager* m_pArrow{ nullptr };

	//CEnemyArrowManager* m_pArrowManager{ nullptr }; 플레이어 화살 매니저
public:
	CPlayerArcher(CSoundManager* sound, CPlayerArrowManager* arrow) : CObject(sound) {
		m_pArrow = arrow;
	}
	virtual void Init() override final;
	void SetPosition() override final;
	void DrawObject(HDC hdc)override final;
	int Update() override final;
	void Move()override final;
	int Attack() override final;
	int Dead() override final { return 0; };
	void SetFrameType(const int& nType) override final;

	void SetTarget(CObject* enemy)
	{
		if (m_pTarget)
			return;

		if (enemy->ReturnTargeted() <= 2) {
			if (m_vtCoord.GetX() - enemy->ReturnCoord().GetX() <= m_nAttackRange) {
				// 해당 적 타게팅
				m_pTarget = enemy;
				m_bInRange = true;
			}
		}
	}

	void GetUpgrade()override final {};
};