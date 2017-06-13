#pragma once
#include"define.h"
#include"CBattle.h"
#include"CManage.h"
#include"SoundManager.h"
#include"CMainCharacter.h"

#define INGAME_NONE 0
#define INGAME_EXIT -1

#define PHASE_BATTLE 0
#define PHASE_MANAGE 1

class CInGame {
	CSoundManager* m_pSoundManager;

	// �÷��̾� Ŭ����
	CMainCharacter* m_pPlayer;

	// ����� ������ �Ѿ�Դ��� Ȯ��
	bool m_bSet{ false };

	// ������ 2���� ������ ����Ѵ�.
	CBattle* m_pBattlePhase{nullptr};
	CManage* m_pManagePhase{nullptr};
	UINT m_nPhase;

	// �� ������ ��ο��� ���̴� ����
	int m_nGold;
	UINT m_nStage{ 1 };
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
	void LButtonUp(const LPARAM& lParam);
	// Ű���� ��� �޴� �Լ�
	void GetKey(const WPARAM& wParam);

	// ���� �ȿ��� �׷��ִ� �Լ�
	void DrawInGame(HDC hdc);

	// ���� �� ������Ʈ �Լ�
	void Update();

	// �� Phase�� ����
	void SetManagePhase()
	{
		m_nPhase = PHASE_MANAGE;
		// ��Ʋ������� �ߴ� �ൿ�� ����
		delete m_pBattlePhase;
		m_pBattlePhase = nullptr;
		m_pManagePhase = new CManage(m_pSoundManager);
	}
	void SetBattlePhase()
	{
		m_nPhase = PHASE_BATTLE;
		// �Ŵ���������� �ߴ� �ൿ�� ����
		delete m_pManagePhase;
		m_pManagePhase = nullptr;
		m_pBattlePhase = new CBattle(m_nStage, m_nGold, m_pCastle, m_pSoundManager);
	}
};