#include"CBattle.h"

CBattle::CBattle(const UINT & nStage, int & nGold, CItem* castle, CSoundManager * sound) : m_pSoundManager(sound)
{
	m_pCastle = castle;
	m_imgBGBack.Load(TEXT("resource/image/stage/Stage_00_Back.png"));
	m_imgBGFront.Load(TEXT("resource/image/stage/Stage_00_Front1.png"));
	m_pEnemyManager = new CEnemyManager(m_pSoundManager,m_pCastle);
	m_pEnemyManager->Init(nStage);
	m_pArrowManager = new CPlayerArrowManager(m_pSoundManager);
	m_pArcher = new CPlayerArcher(m_pSoundManager, m_pArrowManager);
	m_pArcher->Init();

	if (m_imgBGFront.GetBPP() == 32)
	{
		unsigned char * pCol = 0;
		long w = m_imgBGFront.GetWidth();
		long h = m_imgBGFront.GetHeight();
		for (long y = 0; y < h; y++)
		{
			for (long x = 0; x < w; x++)
			{
				pCol = (unsigned char *)m_imgBGFront.GetPixelAddress(x, y);
				unsigned char alpha = pCol[3];
				if (alpha != 255)
				{
					pCol[0] = ((pCol[0] * alpha) + 128) >> 8;
					pCol[1] = ((pCol[1] * alpha) + 128) >> 8;
					pCol[2] = ((pCol[2] * alpha) + 128) >> 8;
				}
			}
		}
		m_imgBGFront.SetHasAlphaChannel(true);
	}

}

CBattle::~CBattle()
{
	if (m_pArcher)
		delete m_pArcher;
	if (m_pArrowManager)
		delete m_pArrowManager;
}

void CBattle::DrawPhase(HDC hdc, CObject* player)
{
	m_imgBGBack.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SRCCOPY);
	m_pEnemyManager->DrawEnemy(hdc);
	m_pCastle->DrawItem(hdc);
	m_pArcher->DrawObject(hdc);
	player->DrawObject(hdc);
	m_pArrowManager->DrawArrow(hdc);
	m_imgBGFront.Draw(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
}

void CBattle::UpdatePhase()
{
	if (!m_bPause) {
		if (m_pEnemyManager->IsStageEnd()) {
			m_bBattleEnd = true;
			return;
		}
		m_pEnemyManager->Update(m_pArcher);
		m_pEnemyManager->SetTarget(m_pCastle->GetPositionVt(), m_pCastle->GetWidth() / 2);
		//dynamic_cast<CPlayerArcher*>(m_pArcher)->SetTarget();
		m_pArcher->Update();
		m_pArrowManager->Update();
	}
}

int CBattle::GetKey(const WPARAM & wParam, CObject* player)
{
	switch (wParam) {
	case VK_ESCAPE:
		if (!m_bPause)
			m_bPause = true;
		else
			return BATTLE_EXIT;
		break;
	default:
		player->GetKey(wParam);
		break;
	}
	return BATTLE_NONE;
}

int CBattle::LButtonUp(const LPARAM & lParam, CObject * player)
{
	return player->LButtonUp(lParam);
}

void CBattle::LButtonDown(const LPARAM & lParam, CObject * player)
{
	player->LButtonDown(lParam);
}

void CBattle::MouseMove(const LPARAM & lParam, CObject * player)
{
	player->MouseMove(lParam);
}

bool CBattle::IsBattleEnd() const
{
	return m_bBattleEnd;
}
