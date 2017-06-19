#pragma once
#include"define.h"
#include"CSprite.h"
#include"CInGame.h"
#include"SoundManager.h"
#include"CIntro.h"

class CGameSystem {
	// ���� �Ŵ���
	CSoundManager* m_pSoundManager;

	// ��Ʈ�� �̹��� -> �Ŀ� ��Ʈ�� Ŭ������ �ٲ� ��
	CIntro* m_pIntro{ nullptr };

	bool m_bIntro;					// ��Ʈ�θ� ���� ���ΰ�
	bool m_bFixed;					// ��Ʈ�ο��� Ÿ��Ʋ�� �����Ǿ��°�
	bool m_bGameOver{ false };		// ���ӿ��� ȭ���ΰ�
	CImage m_imgGameOver;

	// ���θ޴� ��׶��� �̹���
	CSprite m_spBg;

	// ���θ޴� ������
	CSprite m_spIconStartButton;
	CSprite m_spIconExitButton;

	// ���� ���۹�ư�� ������ �� �����Ҵ�
	CInGame* m_pInGame;

public:

	CGameSystem();
	~CGameSystem();
	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam);
	// ��ο� �Լ�
	void MouseMove(const LPARAM& lParam);
	void LButtonDown(const LPARAM& lParam);
	void LButtonUp(const LPARAM& lParam);
	void DrawGame(HDC hdc);
	void Update();

};
