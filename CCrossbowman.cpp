#include"CCrossbowman.h"

void CCrossbowman::Init()
{
	m_sprImg.GetImage(TEXT("resource/image/enemy/Enemy_Archer_00_Walk.png")
		, TEXT("resource/image/enemy/Enemy_Archer_00_Attack.png")
		, TEXT("resource/image/enemy/Enemy_Archer_00_Dead.png")
		, 12, 10, 6);

	m_bAttackCharge = false;
	m_nFrame = 0;
	m_nFrameType = TYPE_WALK;
	m_nAttackFrame = 5;
	m_nDeadTimer = 0;
	m_bDead = false;
	m_nAttackRange = 200;
	m_bInRange = false;

	// 실제로 할 때는 랜덤으로 값을 바꿔줄 것
	int nTmp = rand() % 5;
	float fTmp = static_cast<float>(nTmp) / 10.f + 1;

	m_vtCoord = { static_cast<float>(rand() % 40),250 + static_cast<float>((5 - nTmp) * 40),fTmp };

	m_nReroad = 60;
	m_nCurrentReroad = 0;

	m_nSpeed = 1;
	m_nHeight = 35;
	m_nWidth = 40;
	SetPosition();
}