#pragma once
#include"CCrusader.h"
#include"CPeasant.h"
#include"CWarrior.h"
#include"CCrossbowman.h"
#include"CKnight.h"
#include"CEnemyList.h"

#include"SoundManager.h"

#include"CCastle.h"
#include"CEnemyArrowManager.h"
#include"CPlayerArrowManager.h"

#define SPAWN_ENEMY			240

#define SPAWN_CRUSADER		3000
#define SPAWN_PEASANT		3001
#define SPAWN_CWARRIOR		3002
#define SPAWN_CROSSBOWMAN	3003
#define SPAWN_KNIGHT		3004

#define STAGE_END			-1
// �Ŵ������� �ؾ��� ��

// ���� ����
// ������ �ൿ ����(�̵�, ����, ����, ��ο�)
// �浹üũ
// ȿ����


// Ʈ����
// ����Ÿ�� ��������  ���� ����(�� ���ڸ�ŭ)

class CTriger {

	int m_nStage{ 0 };							// ��������

	TCHAR m_szPath[30]{ NULL, };				// ������ ���
	int m_nTime{ 0 };							// ���� �ð�
	int m_nEnemyNumber{ 0 };					// �� ����
	int* m_pEnemyType{ nullptr };				// �� ����
	ifstream m_ifsRead;							// ���� �Է� ��Ʈ��
	bool m_bEnd{ false };						// ���� �Է��� �����°�

public:
	//CEnemyList* m_pEnemyList;
	CTriger(int nStage)
	{
		m_nStage = nStage;
		wsprintf(m_szPath, TEXT("triger/stage_%d.txt"), nStage);
		m_ifsRead.open(m_szPath, ios::binary);
		m_ifsRead >> m_nTime;
	}
	~CTriger()
	{
		if (m_pEnemyType)
			delete m_pEnemyType;
		m_ifsRead.close();
	}

	void ResetSpawn()
	{
		m_bEnd = false;
		m_ifsRead.close();
		m_ifsRead.open(m_szPath, ios::binary);
		m_ifsRead >> m_nTime;
	}

	const bool& IsFileEnd() const
	{
		return m_bEnd;
	}

	void Spawn(CEnemyList* enemyList, int nTime, CSoundManager* sound, CEnemyArrowManager* arrow, CItem* castle)
	{
		if (!m_bEnd) {
			if (nTime == m_nTime) {
				if (m_pEnemyType)
					delete m_pEnemyType;
				m_ifsRead >> m_nEnemyNumber;
				m_pEnemyType = new int[m_nEnemyNumber];

				for (int i = 0;i < m_nEnemyNumber;++i) {
					CObject* newObj;
					m_ifsRead >> m_pEnemyType[i];
					switch (m_pEnemyType[i]) {
					case SPAWN_CROSSBOWMAN:
						newObj = new CCrossbowman(sound, arrow, castle, m_nStage);
						break;
					case SPAWN_CRUSADER:
						newObj = new CCrusader(sound, castle, m_nStage);
						break;
					case SPAWN_CWARRIOR:
						newObj = new CWarrior(sound, castle, m_nStage);
						break;
					case SPAWN_PEASANT:
						newObj = new CPeasant(sound, castle, m_nStage);
						break;
					case SPAWN_KNIGHT:
						newObj = new CKnight(sound, castle, m_nStage);
						break;
					default:
						break;
					}
					enemyList->Insert(newObj);
				}

				m_ifsRead >> m_nTime;

				if (m_nTime == -1)
					m_bEnd = true;
			}
		}
	}
	
};

class CEnemyManager {
	CItem* m_pCastle{ nullptr };
	CSoundManager* m_pSoundManager;
	UINT m_nStage;
	int m_nSpawnTimer{ 0 };							// ���� ���� Ÿ�̹�
	CEnemyList* m_pEnemyList{ nullptr };
	CTriger* m_pTriger{ nullptr };
	bool m_bStageEnd{ false };

	CEnemyArrowManager* m_pArrows;

public:
	CEnemyManager(CSoundManager* sound, CItem* castle): m_pSoundManager(sound), m_pCastle(castle)
	{
		m_nSpawnTimer = 0;
		m_pEnemyList = new CEnemyList(sound);
		m_pArrows = new CEnemyArrowManager(sound);
	}

	~CEnemyManager()
	{
		if (m_pTriger)
			delete m_pTriger;
		if (m_pEnemyList)
			delete m_pEnemyList;
		if (m_pArrows)
			delete m_pArrows;
	}

	void Init(const UINT& nStage)
	{ 
		m_nStage = nStage;
		m_nSpawnTimer = 0;
		m_pTriger = new CTriger(m_nStage);
	}

	void DrawEnemy(HDC hdc, bool bIntro = false)
	{
		m_pEnemyList->DrawObj(hdc, bIntro);
		m_pArrows->DrawArrow(hdc);
	}

	void Update(CObject* pPlayerArcher, CPlayerArrowManager* arrow)
	{
		m_pTriger->Spawn(m_pEnemyList, m_nSpawnTimer, m_pSoundManager, m_pArrows, m_pCastle);
		m_pEnemyList->Update();

		m_pArrows->Update();
		m_pEnemyList->PlayerTarget(pPlayerArcher);
		m_pEnemyList->ColisionCheck(arrow);

		if (m_pTriger->IsFileEnd()) {
			if (m_pEnemyList->GetNumber() == 0)
				m_bStageEnd = true;
		}
		else
			m_nSpawnTimer++;
	}

	void Update(CObject** pPlayerArcher, CPlayerArrowManager* arrow, int nNumber)
	{
		m_pTriger->Spawn(m_pEnemyList, m_nSpawnTimer, m_pSoundManager, m_pArrows, m_pCastle);
		m_pEnemyList->Update();

		m_pArrows->Update();
		m_pEnemyList->ColisionCheck(arrow);

		for(int i=0;i<nNumber;++i)
			m_pEnemyList->PlayerTarget(pPlayerArcher[i]);

		if (m_pTriger->IsFileEnd()) {
			if (m_pEnemyList->GetNumber() == 0)
				m_bStageEnd = true;
		}
		else
			m_nSpawnTimer++;
	}

	bool IsStageEnd() const
	{
		return m_bStageEnd;
	}

	void ResetSpawnTimer()
	{
		m_nSpawnTimer = 0;
		m_pTriger->ResetSpawn();
	}
	const bool& IsFileEnd()
	{
		return m_pTriger->IsFileEnd();
	}

	void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		m_pEnemyList->SetTarget(vtPosition, nWidth);
	}
};