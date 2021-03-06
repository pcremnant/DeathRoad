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
	m_vtCoord = { static_cast<float>(960),180 + static_cast<float>((5 - nTmp) * 30),fTmp };
	m_nHeight = 57;
	m_nWidth = 62;
	SetPosition();

	m_nAttack = 30;

	m_nAttackFrame = 4 * 4;
	m_nPower = 15;
};

void CMainCharacter::SetPosition() {
	m_rcPosition.left = m_vtCoord.GetX() - m_nWidth*(2.2f - (m_vtCoord.GetZ())) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.right = m_vtCoord.GetX() + m_nWidth*(2.2f - (m_vtCoord.GetZ())) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.top = m_vtCoord.GetY() - m_nHeight*(2.2f - (m_vtCoord.GetZ()));
	m_rcPosition.bottom = m_vtCoord.GetY() + m_nHeight*(2.2f - (m_vtCoord.GetZ()));
}

void CMainCharacter::DrawObject(HDC hdc, bool bIntro) {
	m_sprImg.DrawObject(hdc, m_nFrameType, m_nFrame / 4, m_rcPosition);
}

void CMainCharacter::Move() {
	if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
		m_nFrame = 0;
	}
	else
		m_nFrame++;
}
int CMainCharacter::Attack() {

	if (m_nFrame == m_nAttackFrame) {
		m_pSoundManager->PlayEffect(EFFECT_ARCHER_ATTACK_00);
		
		float fRange = sqrt(pow((m_vtMouse.GetX() - m_vtCoord.GetX()), 2) + pow((m_vtMouse.GetY() - m_vtCoord.GetY()), 2));
		
		if (m_nPower < fRange) {
			m_vtDirect.SetX(-abs(m_nPower*cos(m_fAngle)));
			if(m_vtMouse.GetY()>m_vtCoord.GetY())
				m_vtDirect.SetY(m_nPower*sin(m_fAngle));
			else
				m_vtDirect.SetY(-m_nPower*sin(m_fAngle));
		}
		else {
			m_vtDirect.SetX(-abs(fRange*cos(m_fAngle)));
			if (m_vtMouse.GetY()>m_vtCoord.GetY())
				m_vtDirect.SetY(fRange*sin(m_fAngle));
			else
				m_vtDirect.SetY(-fRange*sin(m_fAngle));
		}
		m_vtDirect.SetZ(m_vtCoord.GetZ());
	
		m_pArrow->CreateArrow(new CPlayerArrow(m_vtCoord, m_nAttack, m_vtDirect, true));
	}


	if (m_nFrame == m_nAttackFrame - 1 && m_bClick)
		;
	else if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
		SetFrameType(TYPE_WALK);
	}
	else
	{
		m_nFrame++;
	}
	return 0;
}

void CMainCharacter::SetFrameType(const int &nType) {
	if (nType <= 2 && nType >= 0) {
		m_nFrameType = nType;
		m_nFrame = 0;
	}
}
int CMainCharacter::Update() {
	int tmp = 0;
	if (m_nFrameType == TYPE_WALK)
		Move();
	else if (m_nFrameType == TYPE_ATTACK)
		tmp = Attack();
	return tmp;
}
int CMainCharacter::GetKey(const WPARAM&wParam) {
	if (m_nFrameType == TYPE_ATTACK)
		return UNIT_NONE;

	switch (wParam) {
	case VK_UP:
	case 'w':
	case 'W':
		if (m_vtCoord.GetZ() > MAXZ) {
			m_vtCoord.SetZ(m_vtCoord.GetZ());
		}
		else {
			
			m_nMoving = { static_cast<float>(0),static_cast<float>(-27),static_cast<float>(1) / 10.f };

			m_vtCoord.Move(m_nMoving, true);
			SetPosition();
		}
		break;
	case VK_DOWN:
	case 'S':
	case 's':
		if (m_vtCoord.GetZ() < MINZ) {
			m_vtCoord.SetZ(m_vtCoord.GetZ());
		}
		else {
			m_nMoving = { static_cast<float>(0),static_cast<float>(27),static_cast<float>(-1) / 10.f };
			m_vtCoord.Move(m_nMoving, true);
			SetPosition();
		}
		break;

	}
	return m_vtCoord.GetZ();
}
void CMainCharacter::MouseMove(const LPARAM&lParam) {
	m_vtMouse = {
		static_cast<float>(LOWORD(lParam)),
		static_cast<float>(HIWORD(lParam)),
		m_vtCoord.GetZ()
	};
	CVector3D vtTmp;
	vtTmp = m_vtMouse;
	vtTmp -= m_vtCoord;
	m_fAngle = acos(vtTmp.GetX() / sqrt(vtTmp.GetX()*vtTmp.GetX() + vtTmp.GetY()*vtTmp.GetY()));
}
void CMainCharacter::LButtonDown(const LPARAM&lParam) {
	SetFrameType(TYPE_ATTACK);
	m_bClick = true;
	m_vtMouse = {
		static_cast<float>(LOWORD(lParam)),
		static_cast<float>(HIWORD(lParam)),
		m_vtCoord.GetZ()
	};
	CVector3D vtTmp;
	vtTmp = m_vtMouse;
	vtTmp -= m_vtCoord;
	m_fAngle = acos(vtTmp.GetX() / sqrt(vtTmp.GetX()*vtTmp.GetX() + vtTmp.GetY()*vtTmp.GetY()));
}
int CMainCharacter::LButtonUp(const LPARAM&lParam) {
	m_bClick = false;
	return m_nAttack;
}

