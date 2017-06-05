#pragma once
#include"define.h"
#include"CInGame.h"

class CGameSystem {
	// ��׶��� �̹���
	CImage m_imgBg;
	UINT m_nSizeBgX;
	UINT m_nSizeBgY;

	// ���� ���۹�ư�� ������ �� �����Ҵ�
	CInGame* m_pInGame;

public:

	CGameSystem()
	{
		m_imgBg.Load(TEXT("resource/intro/bg_00.bmp"));
		m_nSizeBgX = m_imgBg.GetWidth();
		m_nSizeBgY = m_imgBg.GetHeight();
	}

	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam) {
		// m_pInGame�� nullptr�� �ƴ� �� m_pInGame�� �Լ��� ����
		if (m_pInGame)
			m_pInGame->GetKey(wParam);
		else {
			switch (wParam) {
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}
	}

	// ��ο� �Լ�
	void DrawGame(HDC hdc)
	{
		if (m_pInGame)
			m_pInGame->DrawInGame(hdc);
	}
};
