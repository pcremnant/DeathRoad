#pragma once
#include"CItem.h"
#include"CCastle.h"

class CEnemyArrow : public CItem {
protected:
	float m_fGravity{ 0 };					// 화살에 작용하는 중력
	bool m_bColision{ false };				// 화살이 충돌했는가
	bool m_bDelete{ false };				// 화살을 지워야 하는가
	int m_nDeleteTimer{ 0 };				// 화살이 충돌하고 일정시간 지나면 화살을 지워주도록 세는 변수

	CItem* m_pCastle{ nullptr };

public:
	CEnemyArrow(CItem* castle) : CItem() {
		m_pCastle = castle;
	}
	virtual void Init() override = 0;
	virtual void Move() override final;
	void DrawItem(HDC hdc, bool bIntro = false) override final;
	const bool& IsDelete()  const;
protected:
	void SetPosition();
};