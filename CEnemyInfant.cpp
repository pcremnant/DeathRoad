#include"CEnemyInfant.h"

void CEnemyInfant::Init()
{
	m_sprImg.GetImage(TEXT("resource/image/enemy/Enemy_Infant_00_Walk.png")
		, TEXT("resource/image/enemy/Enemy_Infant_00_Attack.png")
		, TEXT("resource/image/enemy/Enemy_Infant_00_Dead.png")
		, 9, 19, 8);
	m_bAttackCharge = false;
	m_nFrame = 0;
	m_nFrameType = TYPE_WALK;
	m_nDeadTimer = 0;
	m_bDead = false;
	m_nAttackRange = 30;
	m_bInRange = false;

	// 실제로 할 때는 랜덤으로 값을 바꿔줄 것
	int nTmp = rand() % 5;
	float fTmp = static_cast<float>(nTmp) / 10.f + 1;

	m_vtCoord = { static_cast<float>(rand()%40),250 + static_cast<float>((5- nTmp) * 40),fTmp };

	m_nSpeed = 4;
	// 124 114
	m_nHeight = 57;
	m_nWidth = 62;
	SetPosition();
}

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

void CEnemyInfant::Move()
{

	if (m_rcPosition.right >= CLIENT_WIDTH)
		m_vtCoord.SetX(0);
	else if (m_bInRange && m_nFrameType == TYPE_WALK) {
		// 사거리 안일 때
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

void CEnemyInfant::SetFrameType(const int & nType)
{
	if (nType <= 2 && nType >= 0) {
		m_nFrameType = nType;
		m_nFrame = 0;
	}
}

