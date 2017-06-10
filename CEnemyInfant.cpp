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
}

int CEnemyInfant::Update()
{
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

/*
void CEnemyInfant::Move()
{

	if (m_rcPosition.right >= CLIENT_WIDTH)
		m_vtCoord.SetX(0);
	else if (m_bInRange && m_nFrameType == TYPE_WALK) {
		// ��Ÿ� ���� ��
		SetFrameType(TYPE_ATTACK);
	}
	else {
		if (m_nFrameType == TYPE_WALK)
			m_vtCoord.Move(m_nSpeed, 0);
		else if (m_nFrameType == TYPE_DEAD && m_nFrame / 4 != m_sprImg.MaxFrame(m_nFrameType) - 1)
			m_vtCoord.Move(0.5f, 0, 0);

	}
	SetPosition();

	if (m_nFrameType == TYPE_DEAD) {
		m_nDeadTimer++;
		if (m_nDeadTimer >= 120)
			m_bDead = true;
		else if ((m_nFrame / 4) == m_sprImg.MaxFrame(m_nFrameType) - 1)
			;
		else
			m_nFrame++;
	}
	else {
		if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
			m_nFrame = 0;
			if (m_nFrameType == TYPE_ATTACK) {
				if (rand() % 2)
					SetFrameType(TYPE_DEAD);
			}
		}
		else
			m_nFrame++;
	}
}
*/


// TYPE_WALK �� ��
void CEnemyInfant::Move()
{

	if (m_rcPosition.right >= CLIENT_WIDTH)
		m_vtCoord.SetX(0);
	else if (m_bInRange) {
		// ��Ÿ� ���� ��
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

// TYPE_ATTACK �� ��
int CEnemyInfant::Attack()
{
	
	if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
		m_nFrame = 0;
		if (m_nFrameType == TYPE_ATTACK) {
			if (rand() % 2)
				SetFrameType(TYPE_DEAD);
		}
		// ���ݷ¸�ŭ ����
		return 10;
	}
	else {
		if (m_nFrame == 7) {
			m_nFrame++;
			return START_ATTACK;
		}
		else
			m_nFrame++;
	}
	return 0;
}

// TYPE_DEAD �� ��
void CEnemyInfant::Dead()
{
	if (m_nFrame / 4 != m_sprImg.MaxFrame(m_nFrameType) - 1)
		m_vtCoord.Move(0.5f, 0, 0);
	m_nDeadTimer++;
	if (m_nDeadTimer >= 120)
		m_bDead = true;
	else if ((m_nFrame / 4) == m_sprImg.MaxFrame(m_nFrameType) - 1)
		;
	else
		m_nFrame++;
}