#pragma once
#include"CItem.h"
#include"CCastle.h"
#include"CEnemyInfant.h"
#include"CEnemyArcher.h"
class CArrow :public CItem {
	float m_fAngle;				// 화살 쏘는 각도
	int m_nPower;				// 화살이 날아가는 파워(사거리)
	bool m_bClick;				// 클릭을 했는가
protected:
	bool m_bColision{ false };
	bool m_bDelete{ false };
	void SetPosition();
	int m_nDeleteTimer{ 0 };
//	CEnemy* m_pEnemy{ nullptr };//찬님 따라하기(지우기)
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