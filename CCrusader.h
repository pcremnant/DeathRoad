#pragma once
#include"CEnemyInfant.h"

class CCrusader : public CEnemyInfant {
public:
	CCrusader(CSoundManager* sound) : CEnemyInfant(sound) {  }
	void Init() override final;
};