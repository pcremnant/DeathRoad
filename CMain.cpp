#include"CMain.h"
void CMainCharacter::Init() {
	m_sprImg.GetImage(TEXT("resource/image/player/Player_Character_Wait.png"),
		TEXT("resource/image/player/Player_Character_Attack.png"),
		NULL,
		9, 6, 0);
	m_bAttackCharge = false;
	m_nFrame = 0;
	m_nFrameType = TYPE_WALK;
	int nTmp = 4;
	float fTmp = static_cast<float>(nTmp) / 10.f + 1;
	m_vtCoord = { static_cast<float>(1150),250 + static_cast<float>((5 - nTmp) * 40),fTmp };
	m_nHeight = 57;
	m_nWidth = 62;
	SetPosition();
};
void CMainCharacter::SetPosition() {
	m_rcPosition.left = m_vtCoord.GetX() - m_nWidth*(2.2f - (m_vtCoord.GetZ() / 7 * 6)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.right=m_vtCoord.GetX() + m_nWidth*(2.2f - (m_vtCoord.GetZ() / 7 * 6)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.top = m_vtCoord.GetY() - m_nHeight*(2.2f - (m_vtCoord.GetZ() / 7 * 6));
	m_rcPosition.bottom = m_vtCoord.GetY() + m_nHeight*(2.2f - (m_vtCoord.GetZ() / 7 * 6));
}
void CMainCharacter::DrawObject(HDC hdc) {
	m_sprImg.DrawObject(hdc, m_nFrameType, m_nFrame / 4, m_rcPosition);
}
