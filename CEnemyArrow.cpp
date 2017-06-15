#include "CEnemyArrow.h"

void CEnemyArrow::DrawItem(HDC hdc)
{
	m_imgBitmap.TransparentBlt(hdc, m_rcPosition.left, m_rcPosition.top, m_nWidth * 2, m_nHeight * 2, 0, 0, m_nWidth * 2, m_nHeight * 2, RGB(255, 255, 255));
}

const bool & CEnemyArrow::IsDelete() const
{
	return m_bDelete;
}

void CEnemyArrow::Move()
{
	if (!m_bColision && !m_bDelete) {
		if (m_vtCoord.GetX() >= m_pCastle->GetPositionVt().GetX() - m_pCastle->GetWidth() / 2 * (2 - m_vtCoord.GetZ() * 5 / 7) + 50) {
			m_bColision = true;
			dynamic_cast<CCastle*>(m_pCastle)->GetDamage(m_nValue);
		}
		else {
			m_vtCoord.Move(m_vtDirect);
			m_vtDirect.Move(0, m_fGravity);
		}
		SetPosition();
	}
	else {
		m_nDeleteTimer++;
		if (m_nDeleteTimer >= 120)
			m_bDelete = true;
	}
}


void CEnemyArrow::SetPosition()
{
	m_rcPosition = { static_cast<LONG>(m_vtCoord.GetX() - m_nWidth)
		,static_cast<LONG>(m_vtCoord.GetY() - m_nHeight)
		, static_cast<LONG>(m_vtCoord.GetX() + m_nWidth)
		,static_cast<LONG>(m_vtCoord.GetY() + m_nHeight) };
}