#pragma once
#include"CEnemyInfant.h"
#include"CEnemyList.h"
//#include"SoundManager.h"

#define SPAWN_ENEMY 240

// 매니저에서 해야할 일

// 적군 생성
// 적군의 행동 관리(이동, 공격, 죽음, 드로우)
// 충돌체크
// 효과음

class CEnemyManager {
	UINT m_nStage;
	int m_nSpawnTimer;
	CEnemyList m_enemyList;

	//CSoundManager m_soundManager;
public:
	CEnemyManager()
	{
		m_nSpawnTimer = 0;
	}

	void Init(const UINT& nStage)
	{ 
		m_nStage = nStage;
		m_nSpawnTimer = 0;
		CObject* newObj = new CEnemyInfant;
		m_enemyList.Insert(newObj);
	}

	void DrawEnemy(HDC hdc)
	{
		m_enemyList.DrawObj(hdc);
	}

	void Update()
	{
		m_enemyList.Update();
		m_nSpawnTimer++;

		if (m_nSpawnTimer >= SPAWN_ENEMY) {
			m_nSpawnTimer %= SPAWN_ENEMY;
			int nTmp = rand() % m_nStage + 2;
			for (int i = 0;i < nTmp;++i) {
				CObject* newObj = new CEnemyInfant;
				m_enemyList.Insert(newObj);
			}
		}
	}

	void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		m_enemyList.SetTarget(vtPosition, nWidth);
	}
};