#pragma once
#include"define.h"

class CBattle;
class CManage;

class CInGame {

	// ������ 2���� ������ ����Ѵ�.
	CBattle* m_pBattlePhase;
	CManage* m_pManagePhase;
	UINT m_nPhase;

	// �� ������ ��ο��� ���̴� ����
	int m_nGold;
	UINT m_nStage;
	// �÷��̾��� ���� (���׷��̵� ����)
	// ...

	// ��Ʋ������� ���̴� ����
	

public:
	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam);
	// ���� �ȿ��� �׷��ִ� �Լ�
	void DrawInGame(HDC hdc);
};