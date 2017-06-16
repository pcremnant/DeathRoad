#pragma once
#include"CItem.h"
#include"CCastle.h"
#include"CEnemyInfant.h"
#include"CEnemyArcher.h"
class CArrow :public CItem {
	float m_fAngle;				// ȭ�� ��� ����
	int m_nPower;				// ȭ���� ���ư��� �Ŀ�(��Ÿ�)
	bool m_bClick;				// Ŭ���� �ߴ°�
protected:
	bool m_bColision{ false };
	bool m_bDelete{ false };
	void SetPosition();
	int m_nDeleteTimer{ 0 };
//	CEnemy* m_pEnemy{ nullptr };//���� �����ϱ�(�����)
public:
	CArrow(const CVector3D& vtPosition, const int& nAttack, const int& nPower) : CItem() {
		m_nValue = nAttack;
		m_vtCoord = vtPosition;
		m_nPower = nPower;
	}
	//CArrow(CEnemyArcher* archer) :CEnemyArcher() {

	//}
	void Ready(int,int);
	void DrawItem(HDC hdc)override;
	void Init()override;
	void Move();
	void Update();
//	void LButtonUp(const LPARAM& lParam);
	const bool& IsDelete()const;
};