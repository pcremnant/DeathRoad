#pragma once
#include"CEnemyArcher.h"
#include"CEnemyArrowManager.h"

class CCrossbowman : public CEnemyArcher {
public:
	CCrossbowman(CSoundManager* sound, CEnemyArrowManager* arrow, CItem* castle, const int& nStage) : CEnemyArcher(sound, arrow, castle) { 
		m_nAttack = nStage * 2 + 10;
		m_nMaxHp = nStage * 20 + 40;
		m_nHp = m_nMaxHp;
	}
	void Init() override final;
};