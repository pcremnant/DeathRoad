#include"CWarrior.h"

void CWarrior::Init()
{
	m_sprImg.GetImage(TEXT("resource/image/enemy/Enemy_Infant_02_Walk.png")
		, TEXT("resource/image/enemy/Enemy_Infant_02_Attack.png")
		, TEXT("resource/image/enemy/Enemy_Infant_02_Dead.png")
		, 11, 14, 10);

	m_nAttackFrame = 4;
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

	m_vtCoord = { static_cast<float>(rand() % 40),250 + static_cast<float>((5 - nTmp) * 40),fTmp };

	m_nSpeed = 1;
	// 124 114
	m_nHeight = 40;
	m_nWidth = 50;
	SetPosition();
}