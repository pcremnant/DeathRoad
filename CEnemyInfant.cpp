#include"CEnemyInfant.h"

void CEnemyInfant::SetPosition()
{
	m_rcPosition.left = m_vtCoord.GetX() - m_nWidth*(2.2f - (m_vtCoord.GetZ() / 6 * 5)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.right = m_vtCoord.GetX() + m_nWidth*(2.2f - (m_vtCoord.GetZ() / 6 * 5)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.top = m_vtCoord.GetY() - m_nHeight*(2.2f - (m_vtCoord.GetZ() / 6 * 5));
	m_rcPosition.bottom = m_vtCoord.GetY() + m_nHeight*(2.2f - (m_vtCoord.GetZ() / 6 * 5));
}

void CEnemyInfant::DrawObject(HDC hdc)
{
	m_sprImg.DrawObject(hdc, m_nFrameType, m_nFrame/4, m_rcPosition);

	HBRUSH hBrush, oldBrush;
	float fTmp = static_cast<float>(m_nHp) / static_cast<float>(m_nMaxHp);
	if (fTmp > 0.7)
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
	else if (fTmp > 0.3)
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
	else
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
	if (fTmp < 0)
		fTmp = 0;

	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RECT rcTmp = { m_vtCoord.GetX() + 20,m_vtCoord.GetY() - 20 - m_nHeight,m_vtCoord.GetX() + 20 + 50 * fTmp,m_vtCoord.GetY() - 10 - m_nHeight };
	FillRect(hdc, &rcTmp, hBrush);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(TRANSPARENT);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	rcTmp = { static_cast<LONG>(m_vtCoord.GetX() + 20),static_cast<LONG>(m_vtCoord.GetY() - 20 - m_nHeight),static_cast<LONG>(m_vtCoord.GetX() + 70) ,static_cast<LONG>(m_vtCoord.GetY() - 10 - m_nHeight) };
	FrameRect(hdc, &rcTmp, hBrush);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

int CEnemyInfant::Update()
{
	int tmp = 0;

	if (m_nHp <= 0 && m_nFrameType!=TYPE_DEAD) {
		m_nHp = 0;
		SetFrameType(TYPE_DEAD);
	}

	if (m_nFrameType == TYPE_WALK)
		Move();
	else if (m_nFrameType == TYPE_ATTACK)
		tmp = Attack();
	else
		Dead();
	if (tmp != 0)
		return tmp;
	else
		return 0;
}

// TYPE_WALK 일 때
void CEnemyInfant::Move()
{

	if (m_rcPosition.right >= CLIENT_WIDTH)
		m_vtCoord.SetX(0);
	else if (m_bInRange) {
		// 사거리 안일 때
		SetFrameType(TYPE_ATTACK);
		return;
	}
	else
		m_vtCoord.Move(m_nSpeed, 0);

	SetPosition();

	if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1)
		m_nFrame = 0;
	else
		m_nFrame++;
}

void CEnemyInfant::SetFrameType(const int & nType)
{
	if (nType <= 2 && nType >= 0) {
		m_nFrameType = nType;
		m_nFrame = 0;
	}
}

// TYPE_ATTACK 일 때
int CEnemyInfant::Attack()
{
	if (m_nFrame == m_nAttackFrame) {
		m_pSoundManager->PlayEffect(EFFECT_INFANT_ATTACK_00);
		dynamic_cast<CCastle*>(m_pCastle)->GetDamage(m_nAttack);
	}
	if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
		m_nFrame = 0;
		// 공격력만큼 리턴
		return 10;
	}
	else {
		if (m_nFrame == 7) {
			m_nFrame++;
			return UNIT_ATTACK;
		}
		else
			m_nFrame++;
	}
	return 0;
}

// TYPE_DEAD 일 때
int CEnemyInfant::Dead()
{
	m_nHp = 0;
	int nTmp = UNIT_NONE;
	if (m_nFrame == 0) {
		nTmp = UNIT_DEAD;
		m_pSoundManager->PlayEffect(EFFECT_INFANT_DEAD_00);
	}
	if (m_nFrame / 4 != m_sprImg.MaxFrame(m_nFrameType) - 1)
		m_vtCoord.Move(0.5f, 0, 0);
	m_nDeadTimer++;
	if (m_nDeadTimer >= 120)
		m_bDead = true;
	else if ((m_nFrame / 4) == m_sprImg.MaxFrame(m_nFrameType) - 1)
		;
	else 
		m_nFrame++;

	return nTmp;
}