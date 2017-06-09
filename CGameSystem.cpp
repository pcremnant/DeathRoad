#include"CGameSystem.h"

CGameSystem::CGameSystem()
{
	// 인트로 화면 이미지 불러오기
	m_imgIntro.Load(TEXT("resource/image/intro/bg_00.PNG"));
	m_nSizeIntroX = m_imgIntro.GetWidth();
	m_nSizeIntroY = m_imgIntro.GetHeight();
	m_bIntro = true;

	m_spBg.GetImage(TEXT("resource/image/intro/bg_03.png"), RECT{ 0,0,CLIENT_WIDTH,CLIENT_HEIGHT });
	m_spIconStartButton.GetImage(TEXT("resource/image/Icon/Icon_StartButton.png"), RECT{ 400,130,800,230 }, TEXT("resource/image/Icon/Icon_StartButton_Pointed.png"));
	m_spIconExitButton.GetImage(TEXT("resource/image/Icon/Icon_ExitButton.png"), RECT{ 400,330,800,430 }, TEXT("resource/image/Icon/Icon_ExitButton_Pointed.png"));

	m_pSoundManager = new CSoundManager();
	m_pSoundManager->SetSounds();
	m_pSoundManager->PlayBGM(BGM_INTRO);
}

CGameSystem::~CGameSystem()
{
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
		case VK_SPACE:
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			if (m_bIntro) {
				m_bIntro = false;
				m_pSoundManager->Stop(BGM_INTRO);
				m_pSoundManager->PlayBGM(BGM_MAINMENU);
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
	if (m_pInGame)
		m_pInGame->LButtonDown(lParam);
	else {
		if (m_spIconExitButton.GetPointed()) {
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
		else if (m_bIntro) {
			m_bIntro = false;
			m_pSoundManager->Stop(BGM_INTRO);
			m_pSoundManager->PlayBGM(BGM_MAINMENU);
		}
	}
}

// 드로우 함수

void CGameSystem::DrawGame(HDC hdc)
{
	if (m_pInGame)
		m_pInGame->DrawInGame(hdc);
	else if(m_bIntro) {
		m_imgIntro.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, m_nSizeIntroX, m_nSizeIntroY, SRCCOPY);
	}
	else {
		m_spBg.DrawSprite(hdc);
		m_spIconStartButton.DrawSprite(hdc);
		m_spIconExitButton.DrawSprite(hdc);
	}
}

void CGameSystem::Update()
{
	if (m_pInGame)
		m_pInGame->Update();
}
