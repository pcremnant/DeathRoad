#pragma once
#include"define.h"
#include"CBattle.h"
#include"CManage.h"

#define PHASE_BATTLE 0
#define PHASE_MANAGE 1

class CInGame {
	bool m_bSet{ false };


	// ������ 2���� ������ ����Ѵ�.
	CBattle* m_pBattlePhase;
	CManage* m_pManagePhase;
	UINT m_nPhase;

	// �� ������ ��ο��� ���̴� ����
	int m_nGold;
	UINT m_nStage;
	// �÷��̾��� ���� (���׷��̵� ����)
	// ...
	//CItem* m_pCastle;
	// ��Ʋ������� ���̴� ����
	

public:
	CInGame() {}
	~CInGame();
	// �ʱ�ȭ ���ִ� �Լ�
	void Init();

	void MouseMove(const LPARAM& lParam);
	void LButtonDown(const LPARAM& lParam);

	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam);

	// ���� �ȿ��� �׷��ִ� �Լ�
	void DrawInGame(HDC hdc);;

	// ���� �� ������Ʈ �Լ�
	void Update();
};