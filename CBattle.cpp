#include"CBattle.h"

CBattle::CBattle(const UINT& nStage, int& nGold, CItem* castle, CSoundManager* sound, CUpgrade* upgrade, CObject** pArcher, const int& nNumArcher, CObject* player, CPlayerArrowManager* arrowManager) : m_pSoundManager(sound)
{
	m_pCastle = castle;

	switch (nStage) {
	case 1:
	case 2:
	case 3:
		m_imgBGBack.Load(TEXT("resource/image/stage/Stage_00_Back.png"));
		m_imgBGFront.Load(TEXT("resource/image/stage/Stage_00_Front.png"));
		break;
	case 4: 
	case 5:
	case 6:
		m_imgBGBack.Load(TEXT("resource/image/stage/Stage_01_Back.png"));
		m_imgBGFront.Load(TEXT("resource/image/stage/Stage_01_Front.png"));
		break;
	case 7:
	case 8:
	case 9:
		m_imgBGBack.Load(TEXT("resource/image/stage/Stage_02_Back.png"));
		m_imgBGFront.Load(TEXT("resource/image/stage/Stage_02_Front.png"));
		break;
	default:
		m_imgBGBack.Load(TEXT("resource/image/stage/Stage_00_Back.png"));
		m_imgBGFront.Load(TEXT("resource/image/stage/Stage_00_Front.png"));
		break;
	}

	m_pEnemyManager = new CEnemyManager(m_pSoundManager,m_pCastle);
	m_pEnemyManager->Init(nStage);

	m_pArrowManager = arrowManager;

	m_pPlayer = player;

	m_nNumArcher = nNumArcher;
	m_pArcher = pArcher;

	m_nGetGold = nStage * 100;
	m_pGold = &nGold;

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
	if (m_pEnemyManager->IsStageEnd()) {
		*m_pGold += m_nGetGold;
	}

	delete m_pEnemyManager;
}

void CBattle::DrawPhase(HDC hdc)
{
	m_imgBGBack.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SRCCOPY);
	m_pEnemyManager->DrawEnemy(hdc);
	m_pCastle->DrawItem(hdc);
	for (int i = 0;i < m_nNumArcher;++i) {
		m_pArcher[i]->DrawObject(hdc);
	}
	m_pPlayer->DrawObject(hdc);
	m_pArrowManager->DrawArrow(hdc);
	m_imgBGFront.Draw(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
}

void CBattle::UpdatePhase()
{
	if (!m_bPause) {
		m_pPlayer->Update();
		if (m_pEnemyManager->IsStageEnd()) {
			m_bBattleEnd = true;
			return;
		}
		m_pEnemyManager->Update(m_pArcher, m_pArrowManager, m_nNumArcher);
		m_pEnemyManager->SetTarget(m_pCastle->GetPositionVt(), m_pCastle->GetWidth() / 2);
		for (int i = 0;i < m_nNumArcher;++i) {
			m_pArcher[i]->Update();
		}
		m_pArrowManager->Update();
		if (m_pCastle->ReturnValue() <= 0) {
			m_bGameOver = true;
			// 게임 종료
		}
	}
}

int CBattle::GetKey(const WPARAM & wParam)
{
	switch (wParam) {
	case VK_ESCAPE:
		if (!m_bPause)
			m_bPause = true;
		else
			return BATTLE_EXIT;
		break;
	default:
		m_pPlayer->GetKey(wParam);
		break;
	}
	return BATTLE_NONE;
}

int CBattle::LButtonUp(const LPARAM & lParam)
{
	return m_pPlayer->LButtonUp(lParam);
}

void CBattle::LButtonDown(const LPARAM & lParam)
{
	m_pPlayer->LButtonDown(lParam);
}

void CBattle::MouseMove(const LPARAM & lParam)
{
	m_pPlayer->MouseMove(lParam);
}

bool CBattle::IsBattleEnd() const
{
	return m_bBattleEnd;
}
