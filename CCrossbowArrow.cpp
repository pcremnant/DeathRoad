#include"CCrossbowArrow.h"

CCrossbowArrow::CCrossbowArrow(const CVector3D & vtPosition, const int & nAttack, CItem* castle) : CEnemyArrow(castle)
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

