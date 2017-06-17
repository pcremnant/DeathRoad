#pragma once
#include"CItem.h"
#include"CObject.h"

class CPlayerArrow : public CItem {
protected:
//	CVector3D m_vtTarget{ 0,0,0 };				// ��ǥ�� ������ ��ġ
	float m_fGravity{ 0 };					// ȭ�쿡 �ۿ��ϴ� �߷�
	bool m_bColision{ false };				// ȭ���� �浹�ߴ°�
	bool m_bDelete{ false };				// ȭ���� ������ �ϴ°�
	int m_nDeleteTimer{ 0 };				// ȭ���� �浹�ϰ� �����ð� ������ ȭ���� �����ֵ��� ���� ����
	CObject* m_pTarget{ nullptr };					// ȭ���� �浹�� �� ���� ���󰡰�
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
	bool ColisionCheck(const RECT& rcBox) override				// �浹�ϴ� ������ üũ
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