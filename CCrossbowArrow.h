#pragma once
#include"CEnemyArrow.h"
#include"CCastle.h"
class CCrossbowArrow : public CEnemyArrow {

public:
	CCrossbowArrow(const CVector3D& vtPosition, const int& nAttack, CItem* castle);
	void Init() override final;
private:
};