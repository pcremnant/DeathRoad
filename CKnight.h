#pragma once
#include"CEnemyInfant.h"

class CKnight : public CEnemyInfant {
public:
	CKnight(CSoundManager* sound, CItem* castle, const int& nStage) : CEnemyInfant(sound, castle) { 
		m_nAttack = nStage * 3 + 12;
		m_nMaxHp = nStage * 20 + 50;
		m_nHp = m_nMaxHp;
	}
	void Init() override final;
};