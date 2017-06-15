#pragma once
#include"CItem.h"

#define OBJECT_TYPE_CASTLE 10000
#define OBJECT_TYPE_ARROW 10001

class CCastle : public CItem {
	int m_nMaxHp;
public:
	CCastle(const int& nCurrentHp, const int& nMaxHp) : CItem()
	{
		m_nValue = nCurrentHp;
		m_nMaxHp = nMaxHp;
	}

	void Init() override final;
	void Move() override final;
	void DrawItem(HDC hdc) override final;

	void GetDamage(const int& damage)
	{
		m_nValue -= damage;

		if (m_nValue < 0)
			m_nValue = 0;
	}
	const int& ReturnHp() const
	{
		return m_nValue;
	}
};