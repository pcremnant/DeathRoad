#include"CGameSystem.h"

CGameSystem::CGameSystem()
{
	// ��Ʈ�� ȭ�� �̹��� �ҷ�����
	m_imgBg.Load(TEXT("resource/image/intro/bg_00.PNG"));
	m_nSizeBgX = m_imgBg.GetWidth();
	m_nSizeBgY = m_imgBg.GetHeight();
}

// Ű���� ��� �޴� �Լ�

void CGameSystem::GetKey(const WPARAM & wParam) {
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

void CGameSystem::DrawGame(HDC hdc)
{
	if (m_pInGame)
		m_pInGame->DrawInGame(hdc);
	else {
		m_imgBg.StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, 0, m_nSizeBgX, m_nSizeBgY, SRCCOPY);
	}
}
