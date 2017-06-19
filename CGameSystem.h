#pragma once
#include"define.h"
#include"CSprite.h"
#include"CInGame.h"
#include"SoundManager.h"
#include"CIntro.h"

class CGameSystem {
	// 사운드 매니저
	CSoundManager* m_pSoundManager;

	// 인트로 이미지 -> 후에 인트로 클래스로 바꿀 것
	CIntro* m_pIntro{ nullptr };

	bool m_bIntro;					// 인트로를 보는 중인가
	bool m_bFixed;					// 인트로에서 타이틀이 고정되었는가
	bool m_bGameOver{ false };		// 게임오버 화면인가
	CImage m_imgGameOver;

	// 메인메뉴 백그라운드 이미지
	CSprite m_spBg;

	// 메인메뉴 아이콘
	CSprite m_spIconStartButton;
	CSprite m_spIconExitButton;

	// 게임 시작버튼을 눌렀을 때 동적할당
	CInGame* m_pInGame;

public:

	CGameSystem();
	~CGameSystem();
	// 키보드 명령 받는 함수
	void GetKey(const WPARAM& wParam);
	// 드로우 함수
	void MouseMove(const LPARAM& lParam);
	void LButtonDown(const LPARAM& lParam);
	void LButtonUp(const LPARAM& lParam);
	void DrawGame(HDC hdc);
	void Update();

};
