#include "CPlayerArrow.h"

CPlayerArrow::CPlayerArrow(const CVector3D & vtPosition, const int & nAttack, const CVector3D& vtTarget) : CItem()
{
	m_imgBitmap.Load(TEXT("resource/image/object/Object_Arrow_02.png"));
	m_vtCoord = vtPosition;
	m_fGravity = 0.3f;

	int nTmpWidth = abs(vtPosition.GetX() - vtTarget.GetX());
	int nTmpHeight = abs(vtPosition.GetY() - vtTarget.GetY());
	float fTmpSpeed = -1.2;
	float fTmpHeight = 0;
	int nTmpFrame = 0;

	while (fTmpHeight < nTmpHeight) {
		fTmpHeight += fTmpSpeed;
		fTmpSpeed += m_fGravity;
		nTmpFrame++;
	}

	float fTmpVectorX = nTmpWidth / nTmpFrame;

	m_vtDirect = { -fTmpVectorX,-1.2f };
	m_nValue = nAttack;
	m_nWidth = m_imgBitmap.GetWidth() / 2;
	m_nHeight = m_imgBitmap.GetHeight() / 2;
	m_nObjectType = OBJECT_TYPE_ENEMYARROW;

	SetPosition();
}

void CPlayerArrow::DrawItem(HDC hdc)
{
	m_imgBitmap.TransparentBlt(hdc, m_rcPosition.left, m_rcPosition.top, m_nWidth * 2, m_nHeight * 2, 0, 0, m_nWidth * 2, m_nHeight * 2, RGB(255, 255, 255));
}

const bool & CPlayerArrow::IsDelete() const
{
	return m_bDelete;
}

void CPlayerArrow::Move()
{
	if (m_pTarget && m_pTarget->IsDead())
		m_pTarget = nullptr;

	if (!m_bDelete && (m_vtCoord.GetX() < 0 || m_vtCoord.GetY() > CFunc::FloorFromY(m_vtCoord.GetZ()))) {
		m_bColision = true;
	}
	else if (!m_bColision && !m_bDelete) {
		m_vtCoord.Move(m_vtDirect);
		m_vtDirect.Move(0, m_fGravity);
		SetPosition();
	}
	if(m_bColision) {
		if (m_pTarget) {
			m_vtCoord.SetX(m_pTarget->ReturnCoord().GetX() + m_nWidth*4);
			SetPosition();
		}
		m_nDeleteTimer++;
		if (m_nDeleteTimer >= 120)
			m_bDelete = true;
	}
}


void CPlayerArrow::SetPosition()
{
	m_rcPosition = { static_cast<LONG>(m_vtCoord.GetX() - m_nWidth)
		,static_cast<LONG>(m_vtCoord.GetY() - m_nHeight)
		, static_cast<LONG>(m_vtCoord.GetX() + m_nWidth)
		,static_cast<LONG>(m_vtCoord.GetY() + m_nHeight) };

}