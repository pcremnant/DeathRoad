#pragma once
#include"CEnemyInfant.h"

class CPeasant : public CEnemyInfant {
public:
	CPeasant(CSoundManager* sound,CItem* castle, const int& nStage) : CEnemyInfant(sound, castle) { 
		m_nAttack = nStage + 6;
		m_nMaxHp = 10 * nStage + 30;
		m_nHp = m_nMaxHp;
	}
	void Init() override final;
};