#include"CGameSystem.h"

CGameSystem::CGameSystem()
{
	// 인트로 화면 이미지 불러오기
	m_imgBg.Load(TEXT("resource/image/intro/bg_00.PNG"));
	m_nSizeBgX = m_imgBg.GetWidth();
	m_nSizeBgY = m_imgBg.GetHeight();
}

// 키보드 명령 받는 함수

void CGameSystem::GetKey(const WPARAM & wParam) {
	// m_pInGame이 nullptr이 아닐 때 m_pInGame의 함수를 실행
	if (m_pInGame)
		m_pInGame->GetKey(wParam);
	else {
		switch (wParam) {
		case VK_SPACE:
			if (!m_pInGame) {
				m_pInGame = new CInGame;
				m_pInGame->Init();
			}
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
	}
}

// 드로우 함수

void CGameSystem::DrawGame(HDC hdc)
{
	if (m_pInGame)
		m_pInGame->DrawInGame(hdc);
	else {
		m_imgBg.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, m_nSizeBgX, m_nSizeBgY, SRCCOPY);
	}
}

void CGameSystem::Update()
{
	if (m_pInGame)
		m_pInGame->Update();
}
