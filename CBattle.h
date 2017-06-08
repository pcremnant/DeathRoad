#pragma once
#include"define.h"

#include"CEnemyInfant.h"

class CBattle {
	// ������ �����Ǵ� �ð��� ��� ����
	UINT m_nTimer;

	// �� ������Ʈ��
	// �Ŵ����� ������ ��
	CObject* m_enemy;

	// �÷��̾� ������Ʈ��



public:
	CBattle(const UINT& nStage, int& nGold, const int& nCastleHp) 
	{
		m_enemy = new CEnemyInfant;
		m_enemy->Init();
	};
	~CBattle()
	{
		if (m_enemy)
			delete m_enemy;
	}

	void DrawPhase(HDC hdc) 
	{
		m_enemy->DrawObject(hdc);
	}
	void UpdatePhase() 
	{
		m_enemy->Move();
	}
	void GetKey(const WPARAM& wParam)
	{
		static int nType = 0;
		switch (wParam) {
		case VK_SPACE:
			m_enemy->SetFrameType(nType++ % 3);
			break;
		default:
			break;
		}
	}
};