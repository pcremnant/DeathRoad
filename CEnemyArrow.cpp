#include "CEnemyArrow.h"

void CEnemyArrow::DrawItem(HDC hdc)
{
	m_imgBitmap.TransparentBlt(hdc, m_rcPosition.left, m_rcPosition.top, m_nWidth * 2, m_nHeight * 2, 0, 0, m_nWidth * 2, m_nHeight * 2, RGB(255, 255, 255));
}
