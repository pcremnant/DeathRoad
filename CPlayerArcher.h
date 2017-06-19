#pragma once
#include"CObject.h"
#include"CPlayerArrowManager.h"
#include"CUpgrade.h"

class CPlayerArcher : public CObject {
protected:

	int m_nReroad;
	int m_nCurrentReroad;

	CObject* m_pTarget{ nullptr };
	CPlayerArrowManager* m_pArrow{ nullptr };
public:
	CPlayerArcher(CSoundManager* sound, CPlayerArrowManager* arrow, CUpgrade* upgrade);
	virtual void Init() override final;
	void SetPosition() override final;
	void DrawObject(HDC hdc, bool bIntro = false)override final;
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
			if (!enemy->IsDead() && m_vtCoord.GetX() - enemy->ReturnCoord().GetX() <= m_nAttackRange) {
				// 해당 적 타게팅
				enemy->GetTarget();
				m_pTarget = enemy;
				m_bInRange = true;
			}
		}
	}

	void GetUpgrade()override final {};
};