#pragma once
#include"CEnemyInfant.h"

class CWarrior : public CEnemyInfant {
public:
	CWarrior(CSoundManager* sound) : CEnemyInfant(sound) {}
	void Init() override final;
};