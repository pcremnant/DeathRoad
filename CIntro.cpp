#include"CIntro.h"

CIntro::CIntro()
{
	m_pSound = new CSoundManager;
	m_pCastle = new CCastle;
	m_pCastle->Init();
	m_pEnemyManager = new CEnemyManager(m_pSound, m_pCastle);
	m_pEnemyManager->Init(0);
	m_imgBGBack.Load(TEXT("resource/image/stage/Stage_00_Back.png"));
	m_imgBGFront.Load(TEXT("resource/image/stage/Stage_00_Front1.png"));

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

CIntro::~CIntro()
{
	if (m_pSound)
		delete m_pSound;
	if (m_pCastle)
		delete m_pCastle;
	if (m_pEnemyManager)
		delete m_pEnemyManager;
}

void CIntro::Update()
{
	m_pEnemyManager->Update();
	m_pEnemyManager->SetTarget(m_pCastle->GetPositionVt(), m_pCastle->GetWidth() / 2);
	if (m_pEnemyManager->IsFileEnd())
		m_pEnemyManager->ResetSpawnTimer();
}

void CIntro::DrawIntro(HDC hdc)
{
	m_imgBGBack.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SRCCOPY);
	m_pEnemyManager->DrawEnemy(hdc);
	m_pCastle->DrawItem(hdc);
	m_imgBGFront.Draw(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
}
