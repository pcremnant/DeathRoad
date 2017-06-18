#pragma once
#include"CObject.h"
#include"CPlayerArrowManager.h"
#include"CArrow.h"

#define MAXZ 1.4
#define MINZ 1.0
class CMainCharacter :public CObject {
	bool m_bClick;
	CVector3D m_nMoving;
	int m_nDamage;
	CVector3D m_vtMouse;
	CPlayerArrowManager* m_pArrow{nullptr};
	CObject* m_pTarget{nullptr};
public:
	CMainCharacter(CSoundManager* sound) : CObject(sound) {
		
	}

	void Init()override;
	void DrawObject(HDC hdc, bool bIntro = false)override;
	void SetPosition()override;
	void SetFrameType(const int& nType)override final;
	void Move()override;
	int GetKey(const WPARAM& wParam) override;		// 키보드 받는 함수
	void MouseMove(const LPARAM& lParam) override;		// 마우스 관련 함수들
	void LButtonDown(const LPARAM& lParam) override;
	int LButtonUp(const LPARAM& lParam) override;	// 공격력
	int Update()override final;
	int Attack()override final;
	int Dead()override final { return 0; };
};