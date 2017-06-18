#pragma once
#include"CObject.h"
#include"CPlayerArrowManager.h"

#define MAXZ 1.4
#define MINZ 1.0
class CMainCharacter :public CObject {
	bool m_bClick{ false };
	CVector3D m_nMoving;
	float m_fGravity{ 0 };
	float m_fAngle;				// ȭ�� ��� ����
	int m_nPower;
	int m_nDamage;
	CVector3D m_vtMouse;
	CPlayerArrowManager* m_pArrow{ nullptr };
	CObject* m_pTarget{ nullptr };
	CVector3D m_vtDirect{ 0,0,0 };
public:
	CMainCharacter(CSoundManager* sound, CPlayerArrowManager* arrow) : CObject(sound) {
		m_pArrow = arrow;
	}
	void Init()override;
	void DrawObject(HDC hdc, bool bIntro = false)override;
	void SetPosition()override;
	void SetFrameType(const int& nType)override final;
	void Move()override;
	int GetKey(const WPARAM& wParam) override;		// Ű���� �޴� �Լ�
	void MouseMove(const LPARAM& lParam) override;		// ���콺 ���� �Լ���
	void LButtonDown(const LPARAM& lParam) override;
	int LButtonUp(const LPARAM& lParam) override;	// ���ݷ�
	int Update()override final;
	int Attack()override final;
	int Dead()override final { return 0; };
	void Ready();
	void Shot();
};