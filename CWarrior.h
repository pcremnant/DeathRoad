#pragma once
#include"CEnemyInfant.h"

class CWarrior : public CEnemyInfant {
public:
	CWarrior(CSoundManager* sound, CItem* castle) : CEnemyInfant(sound,castle) {}
	void Init() override final;
};