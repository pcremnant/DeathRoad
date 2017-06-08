#pragma once
#include"define.h"

#include"CEnemyInfant.h"

class CBattle {
	// 적군이 생성되는 시간을 재는 변수
	UINT m_nTimer;

	// 적 오브젝트들
	// 매니저로 관리할 것
	CObject* m_enemy;

	// 플레이어 오브젝트들



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