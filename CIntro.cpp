#include"CIntro.h"

CIntro::CIntro()
{
	m_pSound = new CSoundManager;
	m_pCastle = new CCastle(10000, 10000);
	m_pCastle->Init();
	m_pEnemyManager = new CEnemyManager(m_pSound, m_pCastle);
	m_pEnemyManager->Init(0);
	m_imgBGBack.Load(TEXT("resource/image/stage/Stage_00_Back.png"));
	m_imgBGFront.Load(TEXT("resource/image/stage/Stage_00_Front1.png"));

	m_imgTitle.Load(TEXT("resource/image/intro/bg_00_Deathroad.png"));
	m_nTitleWidth = 800;
	m_nTitleHeight = 200;
	m_rcTitle = { 200,-200,200 + m_nTitleWidth,-200 + m_nTitleHeight };
	m_bFixed = false;

	m_imgPressAnyKey.Load(TEXT("resource/image/intro/Intro_PressAnyKey.png"));
	m_nPressWidth = 600;
	m_nPressHeight = 100;
	m_rcPressAnyKey = { 300,450,300 + m_nPressWidth,450 + m_nPressHeight };

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

	m_nArcherNumber = INTRO_ARCHER_NUMBER;
	m_pArrow = new CPlayerArrowManager(m_pSound);
	for (int i = 0;i < m_nArcherNumber;++i) {
		m_pArcher[i] = new CPlayerArcher(m_pSound, m_pArrow);
		m_pArcher[i]->Init();
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
	if (m_pArrow)
		delete m_pArrow;
	for (int i = 0;i < m_nArcherNumber;++i)
		delete m_pArcher[i];

}

void CIntro::Update()
{
	m_pEnemyManager->Update(m_pArcher, m_pArrow, m_nArcherNumber);
	m_pEnemyManager->SetTarget(m_pCastle->GetPositionVt(), m_pCastle->GetWidth() / 2);
	for (int i = 0;i < m_nArcherNumber;++i) {
		m_pArcher[i]->Update();
	}
	m_pArrow->Update();

	if (m_pEnemyManager->IsFileEnd())
		m_pEnemyManager->ResetSpawnTimer();

	SetTitle();
}

void CIntro::DrawIntro(HDC hdc)
{
	m_imgBGBack.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SRCCOPY);
	m_pEnemyManager->DrawEnemy(hdc, true);
	m_pCastle->DrawItem(hdc, true);
	for (int i = 0;i < m_nArcherNumber;++i) {
		m_pArcher[i]->DrawObject(hdc);
	}
	m_pArrow->DrawArrow(hdc);
	m_imgBGFront.Draw(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	m_imgTitle.TransparentBlt(hdc, m_rcTitle.left, m_rcTitle.top, m_nTitleWidth, m_nTitleHeight
		, 0, 0, m_imgTitle.GetWidth(), m_imgTitle.GetHeight(), RGB(255, 255, 255));

	if (m_bFixed) {
		m_imgPressAnyKey.TransparentBlt(hdc, m_rcPressAnyKey.left, m_rcPressAnyKey.top, m_nPressWidth, m_nPressHeight
			, 0, 0, m_imgPressAnyKey.GetWidth(), m_imgPressAnyKey.GetHeight(), RGB(0, 0, 0));
	}
}

void CIntro::SetTitle()
{
	if (!m_bFixed) {
		m_rcTitle.top += 2;
		m_rcTitle.bottom += 2;
		if (m_rcTitle.top >= CLIENT_HEIGHT / 2 - 200)
			m_bFixed = true;
	}
}
