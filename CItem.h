#pragma once
#include"define.h"
#include"CVector3D.h"

#define OBJECT_TYPE_CASTLE 700
#define OBJECT_TYPE_ENEMYARROW 701
#define OBJECT_TYPE_PLAYERARROW 702

// 움직일 때 애니메이션이 없는 오브젝트
class CItem {
protected:
	CImage m_imgBitmap;

	// 물체의 위치값
	CVector3D m_vtCoord{ 0,0,0 };
	int m_nWidth{ 0 };
	int m_nHeight{ 0 };
	
	RECT m_rcPosition{ 0,0,0,0 };

	CVector3D m_vtDirect{ 0,0,0 };

	// 물체가 가지고 있는 값
	int m_nValue{ 0 };											//성이면 체력, 화살이면 공격력이 된다.
	int m_nObjectType{ 0 };
public:
	virtual void Init() = 0;
	virtual void Move() = 0;
	virtual void DrawItem(HDC hdc) = 0;

	// 충돌체크를 위한 함수
	const RECT& GetPositionRc() const
	{
		return m_rcPosition;
	}
	const CVector3D& GetPositionVt() const
	{
		return m_vtCoord;
	}
	const int& GetWidth() const
	{
		return m_nWidth;
	}
	const int& GetHeight() const
	{
		return m_nHeight;
	}
	virtual bool ColisionCheck(const RECT& rcBox)
	{
		return false;
	}
	const int& ReturnValue() const
	{
		return m_nValue;
	}	
};