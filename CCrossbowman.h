#pragma once
#include"CEnemyArcher.h"
#include"CEnemyArrowManager.h"

class CCrossbowman : public CEnemyArcher {
public:
	CCrossbowman(CSoundManager* sound, CEnemyArrowManager* arrow, CItem* castle) : CEnemyArcher(sound, arrow, castle) { }
	void Init() override final;
};