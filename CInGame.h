#pragma once
#include"define.h"
#include"CBattle.h"
#include"CManage.h"
#include"SoundManager.h"
#include"CMainCharacter.h"
#include"CUpgrade.h"

#define INGAME_NONE 0
#define INGAME_EXIT -1

#define PHASE_BATTLE 0
#define PHASE_MANAGE 1

class CInGame {
	CSoundManager* m_pSoundManager;

	// 플레이어 클래스
	CMainCharacter* m_pPlayer;

	// 제대로 세팅이 넘어왔는지 확인
	bool m_bSet{ false };

	// 페이즈 2개를 번갈아 사용한다.
	CBattle* m_pBattlePhase{nullptr};
	CManage* m_pManagePhase{nullptr};
	UINT m_nPhase;

	// 두 페이즈 모두에서 쓰이는 변수
	int m_nGold{ 0 };
	UINT m_nStage{ 1 };
	CObject** m_pArcher{ nullptr };
	int m_nNumArcher{ 0 };
	// 플레이어의 상태 (업그레이드 상태)
	CUpgrade* m_pUpgrade{ nullptr };
	CItem* m_pCastle{ nullptr };
	// 배틀페이즈에서 쓰이는 변수
	

public:
	CInGame(CSoundManager* sound);
	~CInGame();
	// 초기화 해주는 함수
	void Init();

	void MouseMove(const LPARAM& lParam);
	int LButtonDown(const LPARAM& lParam);
	void LButtonUp(const LPARAM& lParam);
	// 키보드 명령 받는 함수
	void GetKey(const WPARAM& wParam);

	// 게임 안에서 그려주는 함수
	void DrawInGame(HDC hdc);

	// 게임 안 업데이트 함수
	void Update();

	// 각 Phase를 세팅
	void SetManagePhase()
	{
		m_nPhase = PHASE_MANAGE;
		// 배틀페이즈에서 했던 행동들 저장
		delete m_pBattlePhase;
		m_pBattlePhase = nullptr;
		m_pManagePhase = new CManage(m_pSoundManager);
	}
	void SetBattlePhase()
	{
		m_nPhase = PHASE_BATTLE;
		// 매니지페이즈에서 했던 행동들 저장
		delete m_pManagePhase;
		m_pManagePhase = nullptr;
		m_pBattlePhase = new CBattle(m_nStage, m_nGold, m_pCastle, m_pSoundManager, m_pUpgrade, m_pArcher, m_nNumArcher, m_pPlayer);
	}
};