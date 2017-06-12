#include"CArrow.h"

void CArrow::Init() {
	m_imgBitmap.Load(TEXT("resource/image/Object/Object_Arrow_00.png"));
	m_nHeight = m_imgBitmap.GetHeight();
	m_nWidth = m_imgBitmap.GetWidth();
	m_nObjectType = OBJECT_TYPE_ARROW;
	m_nValue = 100;
	m_vtCoord = {
		static_cast<float>(m_nWidth / 2),static_cast<float>(m_nHeight / 2),static_cast<float>()
	};
	m_rcPosition = {

	};
	m_nCoorinate = { 0,0 };
	m_nDirection_Vector={}
}

void CArrow::Ready(int mx, int my, bool Click,RECT pos) {
	m_nPower = 0;
	m_nCross = sqrt(pow(mx, 2) + pow(my, 2));
	while (!Click) {
		if (m_nPower >= m_nCross)
			m_nPower = m_nCross;
		else {
			m_nPower++;
		}

	}
	m_nAngle = atan2f(static_cast<float>(my) - pos.top, static_cast<float>(mx) - pos.left)*180/3.14;
	
	m_nFy = tanf(m_nAngle);
	

}
void CArrow::Move() {
	



}