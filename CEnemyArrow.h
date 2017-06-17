#pragma once
#include"CItem.h"
#include"CCastle.h"

class CEnemyArrow : public CItem {
protected:
	float m_fGravity{ 0 };					// ȭ�쿡 �ۿ��ϴ� �߷�
	bool m_bColision{ false };				// ȭ���� �浹�ߴ°�
	bool m_bDelete{ false };				// ȭ���� ������ �ϴ°�
	int m_nDeleteTimer{ 0 };				// ȭ���� �浹�ϰ� �����ð� ������ ȭ���� �����ֵ��� ���� ����

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