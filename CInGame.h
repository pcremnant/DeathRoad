#pragma once
#include"define.h"
#include"CBattle.h"
#include"CManage.h"

#define PHASE_BATTLE 0
#define PHASE_MANAGE 1

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
	// �ʱ�ȭ ���ִ� �Լ�
	void Init();

	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam);

	// ���� �ȿ��� �׷��ִ� �Լ�
	void DrawInGame(HDC hdc);;

	// ���� �� ������Ʈ �Լ�
	void Update();
};