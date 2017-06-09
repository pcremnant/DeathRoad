#pragma once
#include"define.h"
#include"CSprite.h"
#include"CInGame.h"

class CGameSystem {
	// 인트로 이미지 -> 후에 인트로 클래스로 바꿀 것
	CImage m_imgIntro;
	UINT m_nSizeIntroX;
	UINT m_nSizeIntroY;
	bool m_bIntro;

	// 메인메뉴 백그라운드 이미지
	CSprite m_spBg;

	// 메인메뉴 아이콘
	CSprite m_spIconStartButton;
	CSprite m_spIconExitButton;

	// 게임 시작버튼을 눌렀을 때 동적할당
	CInGame* m_pInGame;

public:

	CGameSystem();
	// 키보드 명령 받는 함수
	void GetKey(const WPARAM& wParam);
	// 드로우 함수
	void MouseMove(const LPARAM& lParam);
	void LButtonDown(const LPARAM& lParam);
	void DrawGame(HDC hdc);
	void Update();

};
