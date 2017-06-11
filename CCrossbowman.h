#pragma once
#include"CEnemyArcher.h"

class CCrossbowman : public CEnemyArcher {
public:
	CCrossbowman(CSoundManager* sound) : CEnemyArcher(sound) { }
	void Init() override final;
};