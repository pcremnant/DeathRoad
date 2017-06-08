#pragma once
#include"define.h"
#include"CCastle.h"
#include"CEnemyManager.h"

class CBattle {
	CImage m_imgBGBack;
	CImage m_imgBGFront;
	CEnemyManager m_enemyManager;
	// 적군이 생성되는 시간을 재는 변수

	UINT m_nTimer;

	// 적 오브젝트들
	// 매니저로 관리할 것
	CObject* m_pEnemy;

	// 플레이어 오브젝트들
	CItem* m_pCastle;


public:
	CBattle(const UINT& nStage, int& nGold, const int& nCastleHp) 
	{
		m_imgBGBack.Load(TEXT("resource/image/stage/Stage_00_Back.png"));
		m_imgBGFront.Load(TEXT("resource/image/stage/Stage_00_Front1.png"));
		m_enemyManager.Init(nStage);

		m_pCastle = new CCastle;
		m_pCastle->Init();

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

	};
	~CBattle()
	{
		if (m_pEnemy)
			delete m_pEnemy;
	}

	void DrawPhase(HDC hdc) 
	{
		m_imgBGBack.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SRCCOPY);
		m_enemyManager.DrawEnemy(hdc);
		//m_imgBGFront.TransparentBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, RGB(255, 255, 255));
		m_pCastle->DrawItem(hdc);
		m_imgBGFront.Draw(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
		//m_enemy->DrawObject(hdc);
	}
	void UpdatePhase() 
	{
		m_enemyManager.Update();
		m_enemyManager.SetTarget(m_pCastle->GetPositionVt(), m_pCastle->GetWidth()/2);
		//m_enemy->Move();
	}
	void GetKey(const WPARAM& wParam)
	{
		static int nType = 0;
		switch (wParam) {
		case VK_SPACE:
			m_pEnemy->SetFrameType(nType++ % 3);
			break;
		default:
			break;
		}
	}
};