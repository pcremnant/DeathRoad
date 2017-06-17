#include"CPlayerArcher.h"

void CPlayerArcher::Init()
{
	m_sprImg.GetImage(TEXT("resource/image/player/Player_Archer_00_Wait.png")
		, TEXT("resource/image/player/Player_Archer_00_Attack.png")
		, TEXT("resource/image/player/Player_Archer_00_Wait.png")
		, 9, 8, 1);

	m_bAttackCharge = false;
	m_nFrame = 0;
	m_nFrameType = TYPE_WALK;
	m_nAttackFrame = 4*4;
	m_bDead = false;
	m_nAttackRange = 600;
	m_bInRange = false;

	// 실제로 할 때는 랜덤으로 값을 바꿔줄 것
	int nTmp = rand() % 5;
	float fTmp = static_cast<float>(nTmp) / 10.f + 1;

	m_vtCoord = { static_cast<float>(rand() % 40 + 900),150 + static_cast<float>((5 - nTmp) * 20),fTmp };

	m_nReroad = 60;
	m_nCurrentReroad = 0;

	m_nHeight = 35;
	m_nWidth = 40;
	SetPosition();

	m_nAttack = 20;
}

void CPlayerArcher::SetPosition()
{
	m_rcPosition.left = m_vtCoord.GetX() - m_nWidth*(2.2f - (m_vtCoord.GetZ() / 6 * 5)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.right = m_vtCoord.GetX() + m_nWidth*(2.2f - (m_vtCoord.GetZ() / 6 * 5)) + (m_vtCoord.GetZ() - 0.4f) * 10 * 5;
	m_rcPosition.top = m_vtCoord.GetY() - m_nHeight*(2.2f - (m_vtCoord.GetZ() / 6 * 5));
	m_rcPosition.bottom = m_vtCoord.GetY() + m_nHeight*(2.2f - (m_vtCoord.GetZ() / 6 * 5));
}

void CPlayerArcher::DrawObject(HDC hdc)
{
	m_sprImg.DrawObject(hdc, m_nFrameType, m_nFrame / 4, m_rcPosition);
}

int CPlayerArcher::Update()
{
	// 타겟이 죽었으면 타게팅 변수들 초기화
	if (m_pTarget) {
		if (m_pTarget->IsDead()) {
			m_pTarget = nullptr;
			m_bInRange = false;
		}
	}

	int tmp = 0;
	if (m_nFrameType == TYPE_WALK)
		Move();
	else if (m_nFrameType == TYPE_ATTACK)
		tmp = Attack();

	return tmp;
}

// TYPE_WALK 일 때
void CPlayerArcher::Move()
{
	if (m_rcPosition.right >= CLIENT_WIDTH)
		m_vtCoord.SetX(0);
	else if (m_bInRange && !m_bReroad) {
		// 사거리 안일 때
		SetFrameType(TYPE_ATTACK);
		return;
	}

	// 재장전중일때 프레임
	if (m_bReroad) {
		if (m_nReroad <= m_nCurrentReroad) {
			m_bReroad = false;
			m_nCurrentReroad = 0;
		}
		else {
			m_nCurrentReroad++;
		}
		if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1)
			;
		else
			m_nFrame++;
	}
	else {
		if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1)
			m_nFrame = 0;
		else
			m_nFrame++;

	}

	SetPosition();

}

void CPlayerArcher::SetFrameType(const int & nType)
{
	if (nType <= 2 && nType >= 0) {
		m_nFrameType = nType;
		m_nFrame = 0;
	}
}

// TYPE_ATTACK 일 때
int CPlayerArcher::Attack()
{
	if (m_nFrame == m_nAttackFrame) {
		m_pSoundManager->PlayEffect(EFFECT_ARCHER_ATTACK_00);
		CVector3D vtTmp = m_vtCoord;
		vtTmp.SetZ(m_pTarget->ReturnCoord().GetZ());
		m_pArrow->CreateArrow(new CPlayerArrow(vtTmp, m_nAttack, m_pTarget->ReturnCoord()));
		// 화살매니저에 화살을 넣는다.
	}

	if ((m_nFrame / 4) >= m_sprImg.MaxFrame(m_nFrameType) - 1) {
		SetFrameType(TYPE_WALK);
		m_nFrame = 0;

		// 공격력만큼 리턴
		m_bReroad = true;
		m_nCurrentReroad = 0;
		return m_nAttack;
	}
	else
		m_nFrame++;

	return UNIT_NONE;
}

// TYPE_DEAD 일 때
/*int CPlayerArcher::Dead()
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
}*/