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
	//CVector3D m_vtTarget{ 0,0,0 };			// �浹 Ÿ���� ��ǥ	(��)
	//int m_nTargetWidth{ 0 };				// �浹 Ÿ���� �ʺ�	(��)
public:
	CEnemyArrow(CItem* castle) : CItem() {
		m_pCastle = castle;
	}
	virtual void Init() override = 0;
	virtual void Move() override final;
	void DrawItem(HDC hdc) override final;
	const bool& IsDelete()  const;
	//void SetTarget(const CVector3D& vtPosition, const int& nWidth);
protected:
	void SetPosition();
};