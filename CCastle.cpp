#include"CCastle.h"

void CCastle::Init()
{
	m_imgBitmap.Load(TEXT("resource/image/Object/Object_Castle_00.png"));
	m_nHeight = m_imgBitmap.GetHeight();
	m_nWidth = m_imgBitmap.GetWidth();
	m_nObjectType = OBJECT_TYPE_CASTLE;
	m_nValue = 500;
	m_vtCoord = { static_cast<float>(766 + m_nWidth / 2),static_cast<float>(148 + m_nHeight / 2) };
	m_rcPosition = { 
		static_cast<LONG>(m_vtCoord.GetX() - m_nWidth / 2),static_cast<LONG>(m_vtCoord.GetY() - m_nHeight / 2)
		,static_cast<LONG>(m_vtCoord.GetX() + m_nWidth / 2),static_cast<LONG>(m_vtCoord.GetY() + m_nHeight / 2) };
}

void CCastle::Move()
{

}

void CCastle::DrawItem(HDC hdc)
{
	m_imgBitmap.TransparentBlt(hdc, m_rcPosition, RGB(255, 255, 255));
}
