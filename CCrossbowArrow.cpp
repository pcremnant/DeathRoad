#include"CCrossbowArrow.h"

CCrossbowArrow::CCrossbowArrow(const CVector3D & vtPosition, const int & nAttack) : CEnemyArrow()
{
	m_imgBitmap.Load(TEXT("resource/image/object/Object_Arrow_01.png"));
	m_vtCoord = vtPosition;
	m_vtDirect = { 20,-1 };
	m_nValue = nAttack;
	m_fGravity = 0.1;
	m_nWidth = m_imgBitmap.GetWidth() / 2;
	m_nHeight = m_imgBitmap.GetHeight() / 2;
	m_nObjectType = OBJECT_TYPE_ENEMYARROW;
	SetPosition();
}

void CCrossbowArrow::Init() {}

void CCrossbowArrow::Move()
{
	m_vtCoord.Move(m_vtDirect);
	m_vtDirect.Move(0, m_fGravity);
	SetPosition();
}

void CCrossbowArrow::SetPosition()
{
	m_rcPosition = { static_cast<LONG>(m_vtCoord.GetX() - m_nWidth)
		,static_cast<LONG>(m_vtCoord.GetY() - m_nHeight)
		, static_cast<LONG>(m_vtCoord.GetX() + m_nWidth)
		,static_cast<LONG>(m_vtCoord.GetY() + m_nHeight) };
}
