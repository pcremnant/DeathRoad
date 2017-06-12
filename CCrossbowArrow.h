#pragma once
#include"CEnemyArrow.h"

class CCrossbowArrow : public CEnemyArrow {

public:
	CCrossbowArrow(const CVector3D& vtPosition, const int& nAttack);
	void Init() override final;
	void Move() override final;
private:
	void SetPosition();
};