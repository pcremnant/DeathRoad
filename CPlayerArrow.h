#pragma once
#include"CItem.h"

class CPlayerArrow : public CItem {
protected:
	float m_fGravity{ 0 };					// ȭ�쿡 �ۿ��ϴ� �߷�
	bool m_bColision{ false };				// ȭ���� �浹�ߴ°�
	bool m_bDelete{ false };				// ȭ���� ������ �ϴ°�
	int m_nDeleteTimer{ 0 };				// ȭ���� �浹�ϰ� �����ð� ������ ȭ���� �����ֵ��� ���� ����

public:
	CPlayerArrow(const CVector3D & vtPosition, const int & nAttack);
	void Init() override final {};
	virtual void Move() override final;
	void DrawItem(HDC hdc) override final;
	const bool& IsDelete()  const;
protected:
	void SetPosition();
};