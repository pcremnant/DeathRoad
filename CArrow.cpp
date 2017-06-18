#include"CArrow.h"

void CArrow::Init() {
	m_imgBitmap.Load(TEXT("resource/image/Object/Object_Arrow_00.png"));
	m_nHeight = m_imgBitmap.GetHeight()/2;
	m_nWidth = m_imgBitmap.GetWidth()/2;
	m_nObjectType = OBJECT_TYPE_ARROW;
	m_fGravity = 0.3f;
	SetPosition();
}
void CArrow::SetPosition() {
	m_rcPosition = {
		static_cast<LONG>(m_vtCoord.GetX() - m_nWidth),
		static_cast<LONG>(m_vtCoord.GetY() - m_nHeight),
		static_cast<LONG>(m_vtCoord.GetX() + m_nWidth),
		static_cast<LONG>(m_vtCoord.GetY() + m_nHeight)
	};
}
void CArrow::Ready(int mx, int my) {
	m_fAngle = atan2f(static_cast<float>(my) - m_vtCoord.GetX(), static_cast<float>(mx) - m_vtCoord.GetY())*180/3.14;
	m_vtDirect.SetX(m_nPower*cos(m_fAngle));
	m_vtDirect.SetY(m_nPower*sin(m_fAngle));
	m_vtDirect.SetZ(0);
}
void CArrow::Move() {	
	m_vtDirect.SetX(m_nPower*cos(m_fAngle));
	m_vtDirect.SetY(m_nPower*sin(m_fAngle));
	if (!m_bColision && !m_bDelete) {
		m_vtCoord.Move(m_vtDirect);
		m_vtDirect.Move(0, m_fGravity);
		SetPosition();
	}
	if (m_bColision) {
		if (m_pTarget) {
			m_vtCoord.SetX(m_pTarget->ReturnCoord().GetX() + m_nWidth * 4);
			SetPosition();
		}
		m_nDeleteTimer++;
		if (m_nDeleteTimer >= 120)
			m_bDelete = true;
	}
}
void CArrow::DrawItem(HDC hdc,bool BIntro) {
	m_imgBitmap.TransparentBlt(hdc, m_rcPosition.left, m_rcPosition.top, m_rcPosition.right, m_rcPosition.bottom);
}

const bool&CArrow::IsDelete()const {
	return m_bDelete;
}
void CArrow::LButtonUp(const LPARAM&lParam) {
	Move();

}