#pragma once
#include"CItem.h"

class CEnemyArrow : public CItem {
protected:
	float m_fGravity{ 0 };
public:
	CEnemyArrow() : CItem() {}
	virtual void Init() override = 0;
	virtual void Move() override = 0;
	void DrawItem(HDC hdc) override final;
};