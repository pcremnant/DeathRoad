#include"CArrow.h"

void CArrow::Init() {
	m_imgBitmap.Load(TEXT("resource/image/Object/Object_Arrow_00.png"));
	m_nHeight = m_imgBitmap.GetHeight();
	m_nWidth = m_imgBitmap.GetWidth();
	m_nObjectType = OBJECT_TYPE_ARROW;
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
		
		}
		else {
			m_vtCoord.Move(m_vtDirect);
			m_vtDirect.Move(0, -GRAVITY);
		}
		SetPosition();
	}
//	else {
	//	m_nDeleteTimer++;
//		if (m_nDeleteTimer >= 120)
//			m_bDelete = true;
//	}
//}
void CArrow::DrawItem(HDC hdc) {
	m_imgBitmap.TransparentBlt(hdc, m_rcPosition.left, m_rcPosition.top, m_rcPosition.right, m_rcPosition.bottom);
}

const bool&CArrow::IsDelete()const {
	return m_bDelete;
}
void CArrow::Update() {
	Move();
}

//void CArrow::LButtonUp(const LPARAM&lParam) {

//}