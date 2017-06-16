#pragma once
#include"define.h"
#include"SoundManager.h"
#include"CPlayerArrowList.h"

class CPlayerArrowManager {
	CSoundManager* m_pSoundManager;
	CPlayerArrowList* m_pArrowList{ nullptr };
	bool m_bStageEnd{ false };



public:
	CPlayerArrowManager(CSoundManager* sound) : m_pSoundManager(sound)
	{
		m_pArrowList = new CPlayerArrowList();
	}

	~CPlayerArrowManager()
	{
		if (m_pArrowList)
			delete m_pArrowList;
	}

	void CreateArrow(CPlayerArrow* newArrow)
	{
		m_pArrowList->Insert(newArrow);
	}

	void DrawArrow(HDC hdc)
	{
		m_pArrowList->DrawObj(hdc);
	}

	void Update()
	{
		m_pArrowList->Update();
	}
};