#pragma once
#include"CEnemyInfant.h"

class CPeasant : public CEnemyInfant {
public:
	CPeasant(CSoundManager* sound,CItem* castle) : CEnemyInfant(sound, castle) {  }
	void Init() override final;
};