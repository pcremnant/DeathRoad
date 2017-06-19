#include"CGameSystem.h"

CGameSystem::CGameSystem()
{
	// 인트로 화면 이미지 불러오기
	m_pIntro = new CIntro();
	m_bIntro = true;

	m_imgGameOver.Load(TEXT("resource/image/stage/GameOver.png"));

	m_spBg.GetImage(TEXT("resource/image/intro/bg_03.png"), RECT{ 0,0,CLIENT_WIDTH,CLIENT_HEIGHT });
	m_spIconStartButton.GetImage(TEXT("resource/image/Icon/Icon_StartButton.png"), RECT{ 400,130,800,230 }, TEXT("resource/image/Icon/Icon_StartButton_Pointed.png"));
	m_spIconExitButton.GetImage(TEXT("resource/image/Icon/Icon_ExitButton.png"), RECT{ 400,330,800,430 }, TEXT("resource/image/Icon/Icon_ExitButton_Pointed.png"));

	m_pSoundManager = new CSoundManager();
	m_pSoundManager->SetSounds();
	m_pSoundManager->PlayBGM(BGM_INTRO);
}

CGameSystem::~CGameSystem()
{
	if (m_pIntro)
		delete m_pIntro;
	if (m_pInGame)
		delete m_pInGame;
	if (m_pSoundManager)
		delete m_pSoundManager;
}

// 키보드 명령 받는 함수

void CGameSystem::GetKey(const WPARAM & wParam) {
	// m_pInGame이 nullptr이 아닐 때 m_pInGame의 함수를 실행
	if (m_pInGame)
		m_pInGame->GetKey(wParam);
	else {
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			if (m_bGameOver) {
				m_bGameOver = false;
				m_pSoundManager->PlayBGM(BGM_INTRO);
				m_pIntro = new CIntro();
				m_bIntro = true;
				delete m_pInGame;
				m_pInGame = nullptr;
			}
			else if (m_bIntro) {
				m_bIntro = false;
				m_pSoundManager->Stop(BGM_INTRO);
				m_pSoundManager->PlayBGM(BGM_MAINMENU);
				delete m_pIntro;
				m_pIntro = nullptr;
			}
			break;
		}
	}
}

void CGameSystem::MouseMove(const LPARAM & lParam)
{
	if (m_pInGame)
		m_pInGame->MouseMove(lParam);
	else {
		if (!m_bIntro) {
			m_spIconStartButton.InMouse(lParam);
			m_spIconExitButton.InMouse(lParam);
		}
	}
}

void CGameSystem::LButtonDown(const LPARAM & lParam)
{
	if (m_bGameOver) {
		m_bGameOver = false;
		m_pSoundManager->PlayBGM(BGM_INTRO);
		m_pIntro = new CIntro();
		m_bIntro = true;
		delete m_pInGame;
		m_pInGame = nullptr;
	}
	else if (m_pInGame) {
		if (m_pInGame->LButtonDown(lParam) == INGAME_EXIT) {
			delete m_pInGame;
			m_pInGame = nullptr;

		}
	}
	else {
		if (m_bIntro) {
			if (!m_pIntro->IsFixed()) {
				m_pIntro->SetFixed();
			}
			else {
				m_bIntro = false;
				m_pSoundManager->Stop(BGM_INTRO);
				m_pSoundManager->PlayBGM(BGM_MAINMENU);
				delete m_pIntro;
				m_pIntro = nullptr;
			}
		}
		else if (m_spIconExitButton.GetPointed()) {
			m_pSoundManager->PlayEffect(EFFECT_CLICK_BUTTON_00);
			PostQuitMessage(0);
		}
		else if (m_spIconStartButton.GetPointed()) {
			if (!m_pInGame) {
				m_pSoundManager->Stop(BGM_MAINMENU);
				m_pSoundManager->PlayEffect(EFFECT_CLICK_BUTTON_00);
				m_pInGame = new CInGame(m_pSoundManager);
				m_pInGame->Init();
			}
		}
	}
}

void CGameSystem::LButtonUp(const LPARAM & lParam)
{
	if (m_pInGame)
		m_pInGame->LButtonUp(lParam);
}

// 드로우 함수

void CGameSystem::DrawGame(HDC hdc)
{
	if (m_bGameOver) {
		m_imgGameOver.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SRCCOPY);
	}
	else if (m_pInGame)
		m_pInGame->DrawInGame(hdc);
	else if (m_bIntro) {
		m_pIntro->DrawIntro(hdc);
	}
	else {
		m_spBg.DrawSprite(hdc);
		m_spIconStartButton.DrawSprite(hdc);
		m_spIconExitButton.DrawSprite(hdc);
	}
}

void CGameSystem::Update()
{
	if (m_bIntro) {
		m_pIntro->Update();
	}
	else if (m_pInGame) {
		m_pInGame->Update();
		if (m_pInGame->IsGameOver()) {
			m_bGameOver = true;
		}
	}
}
