#pragma once
#include"CEnemyInfant.h"

class CPeasant : public CEnemyInfant {
public:
	CPeasant(CSoundManager* sound) : CEnemyInfant(sound) {  }
	void Init() override final;
};