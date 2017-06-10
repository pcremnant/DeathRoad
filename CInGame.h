#pragma once
#include"define.h"
#include"CBattle.h"
#include"CManage.h"
#include"SoundManager.h"

#define INGAME_NONE 0
#define INGAME_EXIT -1

#define PHASE_BATTLE 0
#define PHASE_MANAGE 1

class CInGame {
	CSoundManager* m_pSoundManager;

	// ����� ������ �Ѿ�Դ��� Ȯ��
	bool m_bSet{ false };

	// ������ 2���� ������ ����Ѵ�.
	CBattle* m_pBattlePhase{nullptr};
	CManage* m_pManagePhase{nullptr};
	UINT m_nPhase;

	// �� ������ ��ο��� ���̴� ����
	int m_nGold;
	UINT m_nStage;
	// �÷��̾��� ���� (���׷��̵� ����)
	// ...
	CItem* m_pCastle{ nullptr };
	// ��Ʋ������� ���̴� ����
	

public:
	CInGame(CSoundManager* sound);
	~CInGame();
	// �ʱ�ȭ ���ִ� �Լ�
	void Init();

	void MouseMove(const LPARAM& lParam);
	int LButtonDown(const LPARAM& lParam);

	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam);

	// ���� �ȿ��� �׷��ִ� �Լ�
	void DrawInGame(HDC hdc);;

	// ���� �� ������Ʈ �Լ�
	void Update();
};