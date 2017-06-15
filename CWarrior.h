#pragma once
#include"CEnemyInfant.h"

class CWarrior : public CEnemyInfant {
public:
	CWarrior(CSoundManager* sound, CItem* castle, const int& nStage) : CEnemyInfant(sound,castle) {
		m_nAttack = nStage * 3 + 10;
		m_nMaxHp = nStage * 40 + 50;
	}
	void Init() override final;
};