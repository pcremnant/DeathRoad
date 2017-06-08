#pragma once
#include"define.h"

#include"CEnemyManager.h"

class CBattle {
	CImage m_imgBGBack;
	CImage m_imgBGFront;
	CEnemyManager m_enemyManager;
	// ������ �����Ǵ� �ð��� ��� ����

	UINT m_nTimer;

	// �� ������Ʈ��
	// �Ŵ����� ������ ��
	CObject* m_enemy;

	// �÷��̾� ������Ʈ��



public:
	CBattle(const UINT& nStage, int& nGold, const int& nCastleHp) 
	{
		m_imgBGBack.Load(TEXT("resource/image/stage/Stage_00_Back.png"));
		m_imgBGFront.Load(TEXT("resource/image/stage/Stage_00_Front1.png"));
		m_enemy = new CEnemyInfant;
		m_enemy->Init();
		m_enemyManager.Init(nStage);


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
		if (m_enemy)
			delete m_enemy;
	}

	void DrawPhase(HDC hdc) 
	{
		m_imgBGBack.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SRCCOPY);
		m_enemyManager.DrawEnemy(hdc);
		//m_imgBGFront.TransparentBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, RGB(255, 255, 255));
		m_imgBGFront.Draw(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
		//m_enemy->DrawObject(hdc);
	}
	void UpdatePhase() 
	{
		m_enemyManager.Update();
		//m_enemy->Move();
	}
	void GetKey(const WPARAM& wParam)
	{
		static int nType = 0;
		switch (wParam) {
		case VK_SPACE:
			m_enemy->SetFrameType(nType++ % 3);
			break;
		default:
			break;
		}
	}
};