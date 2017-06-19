#pragma once
#include"define.h"
#include"CBattle.h"
#include"CManage.h"
#include"SoundManager.h"
#include"CMainCharacter.h"
#include"CUpgrade.h"
#include"CPlayerArrowManager.h"

#define INGAME_NONE 0
#define INGAME_EXIT -1

#define PHASE_BATTLE 0
#define PHASE_MANAGE 1

class CInGame {
	CSoundManager* m_pSoundManager;

	// �÷��̾� Ŭ����
	CObject* m_pPlayer;

	// ����� ������ �Ѿ�Դ��� Ȯ��
	bool m_bSet{ false };
	bool m_bGameOver{ false };
	// ������ 2���� ������ ����Ѵ�.
	CBattle* m_pBattlePhase{nullptr};
	CManage* m_pManagePhase{nullptr};
	UINT m_nPhase;

	// �� ������ ��ο��� ���̴� ����
	int m_nGold{ 10000 };
	UINT m_nStage{ 1 };
	CObject** m_pArcher{ nullptr };
	int m_nNumArcher{ 0 };
	// �÷��̾��� ���� (���׷��̵� ����)
	CUpgrade* m_pUpgrade{ nullptr };
	CItem* m_pCastle{ nullptr };
	// ��Ʋ������� ���̴� ����
	CPlayerArrowManager* m_pArrow{ nullptr };

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
	void SetManagePhase();
	void SetBattlePhase();
	bool IsGameOver() const
	{
		return m_bGameOver;
	}
};