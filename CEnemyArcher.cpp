#include"CEnemyArcher.h"

void CEnemyArcher::SetPosition()
{
	m_rcPosition.left = m_vtCoord.GetX() - m_nWidth*(2.2f - (m_vtCoord.GetZ() / 6 * 5)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.right = m_vtCoord.GetX() + m_nWidth*(2.2f - (m_vtCoord.GetZ() / 6 * 5)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.top = m_vtCoord.GetY() - m_nHeight*(2.2f - (m_vtCoord.GetZ() / 6 * 5));
	m_rcPosition.bottom = m_vtCoord.GetY() + m_nHeight*(2.2f - (m_vtCoord.GetZ() / 6 * 5));
}

void CEnemyArcher::DrawObject(HDC hdc)
{
	m_sprImg.DrawObject(hdc, m_nFrameType, m_nFrame / 4, m_rcPosition);
	if (newArrow)
		newArrow->DrawItem(hdc);
}

int CEnemyArcher::Update()
{
	if (newArrow)
		newArrow->Move();
	int tmp = 0;
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
void CEnemyArcher::Move()
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

void CEnemyArcher::SetFrameType(const int & nType)
{
	if (nType <= 2 && nType >= 0) {
		m_nFrameType = nType;
		m_nFrame = 0;
	}
}

// TYPE_ATTACK 일 때
int CEnemyArcher::Attack()
{
	if (m_nFrame == m_nAttackFrame) {
		m_pSoundManager->PlayEffect(EFFECT_ARCHER_ATTACK_00);
		if (!newArrow)
			newArrow = new CCrossbowArrow(m_vtCoord, 10);
		else {
			delete newArrow;
			newArrow = new CCrossbowArrow(m_vtCoord, 10);
		}
		//CItem* newArrow = new CCrossbowArrow(m_vtCoord, 10);
	}
	if (m_bReroad) {
		if (m_nCurrentReroad < m_nReroad)
			m_nCurrentReroad++;
		else {
			m_nCurrentReroad = 0;
			m_bReroad = false;
		}
	}
	else {
		if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
			m_nFrame = 0;
			if (m_nFrameType == TYPE_ATTACK) {
				if (rand() % 2)
					SetFrameType(TYPE_DEAD);
			}
			// 공격력만큼 리턴
			m_bReroad = true;
			m_nCurrentReroad = 0;
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
	}
	return 0;
}

// TYPE_DEAD 일 때
int CEnemyArcher::Dead()
{
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