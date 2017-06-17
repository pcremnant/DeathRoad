#pragma once
#include"CItem.h"
#include"CCastle.h"
#include"CObject.h"
class CArrow :public CItem {
	float m_fGravity{ 0 };
	float m_fAngle;				// ȭ�� ��� ����
	int m_nPower;				// ȭ���� ���ư��� �Ŀ�(��Ÿ�)
	bool m_bClick;				// Ŭ���� �ߴ°�
	CObject* m_pTarget{ nullptr };
protected:
	bool m_bColision{ false };
	bool m_bDelete{ false };
	void SetPosition();
	int m_nDeleteTimer{ 0 };
public:
	CArrow(const CVector3D& vtPosition, const int& nAttack, const int& nPower) : CItem() {
		m_nValue = nAttack;
		m_vtCoord = vtPosition;
		m_nPower = nPower;
	}
	void DrawItem(HDC hdc, bool bIntro = false) override final;
	void Ready(int,int);
	void Init()override;
	void Move();
	const bool& IsDelete()const;
	void LButtonUp(const LPARAM&lParam);
};