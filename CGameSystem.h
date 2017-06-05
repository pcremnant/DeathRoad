#pragma once
#include"define.h"
#include"CInGame.h"

class CGameSystem {
	// 백그라운드 이미지
	CImage m_imgBg;
	UINT m_nSizeBgX;
	UINT m_nSizeBgY;

	// 게임 시작버튼을 눌렀을 때 동적할당
	CInGame* m_pInGame;

public:

	CGameSystem()
	{
		m_imgBg.Load(TEXT("resource/intro/bg_00.bmp"));
		m_nSizeBgX = m_imgBg.GetWidth();
		m_nSizeBgY = m_imgBg.GetHeight();
	}

	// 키보드 명령 받는 함수
	void GetKey(const WPARAM& wParam) {
		// m_pInGame이 nullptr이 아닐 때 m_pInGame의 함수를 실행
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

	// 드로우 함수
	void DrawGame(HDC hdc)
	{
		if (m_pInGame)
			m_pInGame->DrawInGame(hdc);
	}
};
