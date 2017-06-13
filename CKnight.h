#pragma once
#include"CEnemyInfant.h"

class CKnight : public CEnemyInfant {
public:
	CKnight(CSoundManager* sound, CItem* castle) : CEnemyInfant(sound, castle) {  }
	void Init() override final;
};