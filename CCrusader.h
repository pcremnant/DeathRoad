#pragma once
#include"CEnemyInfant.h"

class CCrusader : public CEnemyInfant {
public:
	CCrusader(CSoundManager* sound,CItem* castle) : CEnemyInfant(sound, castle) {  }
	void Init() override final;
};