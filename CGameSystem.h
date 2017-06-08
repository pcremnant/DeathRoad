#pragma once
#include"define.h"
#include"CInGame.h"

class CGameSystem {
	// ��׶��� �̹���
	CImage m_imgBg;
	UINT m_nSizeBgX;
	UINT m_nSizeBgY;

	// ���� ���۹�ư�� ������ �� �����Ҵ�
	CInGame* m_pInGame;

public:

	CGameSystem();
	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam);
	// ��ο� �Լ�
	void DrawGame(HDC hdc);
	void Update();

};
