#pragma once
#include"define.h"
#include"SoundManager.h"
#include"CEnemyArrowList.h"

class CEnemyArrowManager {
	CSoundManager* m_pSoundManager;
	CEnemyArrowList* m_pArrowList{ nullptr };
	bool m_bStageEnd{ false };



public:
	CEnemyArrowManager(CSoundManager* sound) : m_pSoundManager(sound)
	{
		m_pArrowList = new CEnemyArrowList();
	}

	~CEnemyArrowManager()
	{
		if (m_pArrowList)
			delete m_pArrowList;
	}

	void CreateArrow(CEnemyArrow* newArrow)
	{
		m_pArrowList->Insert(newArrow);
	}

	void DrawArrow(HDC hdc)
	{
		m_pArrowList->DrawObj(hdc);
	}

	/*void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		m_pArrowList->SetTarget(vtPosition, nWidth);
	}*/

	void Update()
	{
		m_pArrowList->Update();
	}
};