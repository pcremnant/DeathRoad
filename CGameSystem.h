#pragma once
#include"define.h"
#include"CSprite.h"
#include"CInGame.h"

class CGameSystem {
	// ��Ʈ�� �̹��� -> �Ŀ� ��Ʈ�� Ŭ������ �ٲ� ��
	CImage m_imgIntro;
	UINT m_nSizeIntroX;
	UINT m_nSizeIntroY;
	bool m_bIntro;

	// ���θ޴� ��׶��� �̹���
	CSprite m_spBg;

	// ���θ޴� ������
	CSprite m_spIconStartButton;
	CSprite m_spIconExitButton;

	// ���� ���۹�ư�� ������ �� �����Ҵ�
	CInGame* m_pInGame;

public:

	CGameSystem();
	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam);
	// ��ο� �Լ�
	void MouseMove(const LPARAM& lParam);
	void LButtonDown(const LPARAM& lParam);
	void DrawGame(HDC hdc);
	void Update();

};
