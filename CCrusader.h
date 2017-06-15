#pragma once
#include"CEnemyInfant.h"

class CCrusader : public CEnemyInfant {
public:
	CCrusader(CSoundManager* sound,CItem* castle, const int& nStage) : CEnemyInfant(sound, castle) { 
		m_nAttack = nStage * 4 + 8;
		m_nMaxHp = nStage * 30 + 80;
		m_nHp = m_nMaxHp;
	}
	void Init() override final;
};