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

void CCastle::DrawItem(HDC hdc, bool bIntro)
{
	m_imgBitmap.TransparentBlt(hdc, m_rcPosition, RGB(255, 255, 255));
	
	if (!bIntro) {
		HBRUSH hBrush, oldBrush;
		float fTmp = static_cast<float>(m_nValue) / static_cast<float>(m_nMaxHp);
		if (fTmp > 0.7)
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
		else if (fTmp > 0.3)
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
		else
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		RECT rcTmp = { 20,20,20 + 500 * fTmp,50 };
		FillRect(hdc, &rcTmp, hBrush);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(TRANSPARENT);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		rcTmp = { 20,20,520,50 };
		FrameRect(hdc, &rcTmp, hBrush);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
	}
}
