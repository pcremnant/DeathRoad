#include"CMainCharacter.h"

void CMainCharacter::Init() {
	m_sprImg.GetImage(TEXT("resource/image/player/Player_Character_Wait.png"),
		TEXT("resource/image/player/Player_Character_Attack.png"),
		TEXT("resource/image/player/Player_Character_Attack.png"),
		9, 6, 1);
	m_bAttackCharge = false;
	m_nFrame = 0;
	m_nFrameType = TYPE_WALK;
	int nTmp = 4;
	float fTmp = static_cast<float>(nTmp) / 10.f + 1;
	m_vtCoord = { static_cast<float>(960),210 + static_cast<float>((5 - nTmp) ),fTmp };
	m_nHeight = 57;
	m_nWidth = 62;
	SetPosition();
};

void CMainCharacter::SetPosition() {
	m_rcPosition.left = m_vtCoord.GetX() - m_nWidth*(2.2f - (m_vtCoord.GetZ() / 6 * 5)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.right = m_vtCoord.GetX() + m_nWidth*(2.2f - (m_vtCoord.GetZ() / 6 * 5)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.top = m_vtCoord.GetY() - m_nHeight*(2.2f - (m_vtCoord.GetZ() / 6 * 5));
	m_rcPosition.bottom = m_vtCoord.GetY() + m_nHeight*(2.2f - (m_vtCoord.GetZ() / 6 * 5));
}

void CMainCharacter::DrawObject(HDC hdc) {
	m_sprImg.DrawObject(hdc, m_nFrameType, m_nFrame / 4, m_rcPosition);
}

void CMainCharacter::Move() {
	if (m_nDirection == 2) {
		if (m_vtCoord.GetZ() >= MAXZ) {
			m_vtCoord.SetZ(0);
		}
		else {
			m_vtCoord.SetZ(0.1);
			SetPosition();
		}
	}
	else if (m_nDirection == 1) {
		if (m_vtCoord.GetZ() <= MINZ) {
			m_vtCoord.SetZ(0);
		}
		else {
			m_vtCoord.SetZ(-0.1);
			SetPosition();
		}
	}
	if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
		m_nFrame = 0;
	}
	else
		m_nFrame++;
}

int CMainCharacter::Attack() {
	if (m_nClick) {
		m_nFrameType = TYPE_ATTACK;
		if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
			m_nFrame = 0;
		}
		else
		{
			if (!m_nClick) {
				m_nFrame++;
				return UNIT_ATTACK;
			}
			else
				m_nFrame++;
		}
	}
}

void CMainCharacter::SetFrameType(const int &nType) {
	if (nType <= 2 && nType >= 0) {
		m_nFrameType = nType;
		m_nFrame = 0;
	}
}
int CMainCharacter::Dead() {
	return 0;
}

int CMainCharacter::Update() {
	int tmp = 0;
	if (m_nFrameType == TYPE_ATTACK)
		tmp = Attack();
	if (tmp != 0)
		return tmp;
	else
		return 0;
}
int CMainCharacter::GetKey(const WPARAM&wParam) {
	switch (wParam) {
	case VK_UP:
	case 'w':
	case 'W':
		if (m_vtCoord.GetZ() >= MAXZ) {
			m_vtCoord.SetZ(m_vtCoord.GetZ());
		}
		else {
			m_nMoving={static_cast<float>(10),static_cast<float>(-20),static_cast<float>(1)/10.f };
			m_vtCoord.Move(m_nMoving, true);
			SetPosition();
		}
		break;
	case VK_DOWN:
	case 'S':
	case 's':
		if (m_vtCoord.GetZ() <= MINZ) {
			m_vtCoord.SetZ(m_vtCoord.GetZ());
		}
		else {
			m_nMoving = { static_cast<float>(-10),static_cast<float>(20),static_cast<float>(-1) / 10.f };
			m_vtCoord.Move(m_nMoving, true);
			SetPosition();
		}
		break;

	}
	return 0;
}
void CMainCharacter::MouseMove(const LPARAM&lParam) {

}
void CMainCharacter::LButtonDown(const LPARAM&lParam) {
	m_nFrame = TYPE_ATTACK;



}
int CMainCharacter::LButtonUp(const LPARAM&lParam) {

	m_nFrame = TYPE_WALK;
	return 0;
}