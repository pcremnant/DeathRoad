#pragma once
#include"CItem.h"
#include"CObject.h"

class CPlayerArrow : public CItem {
protected:
//	CVector3D m_vtTarget{ 0,0,0 };				// 목표한 적군의 위치
	float m_fGravity{ 0 };					// 화살에 작용하는 중력
	bool m_bColision{ false };				// 화살이 충돌했는가
	bool m_bDelete{ false };				// 화살을 지워야 하는가
	int m_nDeleteTimer{ 0 };				// 화살이 충돌하고 일정시간 지나면 화살을 지워주도록 세는 변수
	CObject* m_pTarget{ nullptr };					// 화살이 충돌한 후 적을 따라가게
public:
	CPlayerArrow(const CVector3D & vtPosition, const int & nAttack, const CVector3D& vtTarget);
	void Init() override final {};
	virtual void Move() override final;
	void DrawItem(HDC hdc) override final;
	const bool& IsDelete()  const;
	const bool& IsColision() const
	{
		return m_bColision;
	}
	void SetColision()
	{
		m_bColision = true;
	}
	bool ColisionCheck(const RECT& rcBox) override				// 충돌하는 순간만 체크
	{
		if (IsColision())
			return false;
		bool bTmp = m_vtCoord.ColisionBox(GetWidth(), GetHeight(), rcBox);
		if (bTmp)
			SetColision();
		return bTmp;
	}
	void SetTarget(CObject* target)
	{
		if (!m_pTarget)
			m_pTarget = target;
	}
protected:
	void SetPosition();
};