#pragma once
#include"CObject.h"
#define MAXZ 1.4
#define MINZ 1.0
class CMainCharacter :public CObject {
	bool m_nClick;
	CVector3D m_nMoving;
	int Damage;
public:
	CMainCharacter(CSoundManager* sound) : CObject(sound) {}

	void Init()override;
	void DrawObject(HDC hdc)override;
	void SetPosition()override;
	void SetFrameType(const int& nType)override;
	void Move()override;

	int GetKey(const WPARAM& wParam) override;		// Ű���� �޴� �Լ�
	void MouseMove(const LPARAM& lParam) override;		// ���콺 ���� �Լ���
	void LButtonDown(const LPARAM& lParam) override;
	int LButtonUp(const LPARAM& lParam) override;	// ���ݷ�
	int Update()override;
	int Attack()override;
	int Dead()override;
};