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

	CGameSystem();
	// 키보드 명령 받는 함수
	void GetKey(const WPARAM& wParam);
	// 드로우 함수
	void DrawGame(HDC hdc);
	void Update();

};
