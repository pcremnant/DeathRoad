#pragma once
#include"CCrusader.h"
#include"CPeasant.h"
#include"CWarrior.h"
#include"CEnemyList.h"
#include"SoundManager.h"

#define SPAWN_ENEMY 240

// �Ŵ������� �ؾ��� ��

// ���� ����
// ������ �ൿ ����(�̵�, ����, ����, ��ο�)
// �浹üũ
// ȿ����

class CEnemyManager {
	CSoundManager* m_pSoundManager;
	UINT m_nStage;
	int m_nSpawnTimer;
	CEnemyList* m_pEnemyList;

public:
	CEnemyManager(CSoundManager* sound) : m_pSoundManager(sound)
	{
		m_nSpawnTimer = 0;
		m_pEnemyList = new CEnemyList(sound);
	}

	void Init(const UINT& nStage)
	{ 
		m_nStage = nStage;
		m_nSpawnTimer = 0;
		CObject* newObj = new CWarrior;
		m_pEnemyList->Insert(newObj);
	}

	void DrawEnemy(HDC hdc)
	{
		m_pEnemyList->DrawObj(hdc);
	}

	void Update()
	{
		m_pEnemyList->Update();
		m_nSpawnTimer++;

		if (m_nSpawnTimer >= SPAWN_ENEMY) {
			m_nSpawnTimer %= SPAWN_ENEMY;
			int nTmp = rand() % (m_nStage+2) + 2;
			for (int i = 0;i < nTmp;++i) {
				int random = rand() % 3;
				CObject* newObj;
				if (random == 0)
					newObj = new CPeasant;
				else if (random == 1)
					newObj = new CCrusader;
				else
					newObj = new CWarrior;
				m_pEnemyList->Insert(newObj);
			}
		}
	}

	void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		m_pEnemyList->SetTarget(vtPosition, nWidth);
	}
};