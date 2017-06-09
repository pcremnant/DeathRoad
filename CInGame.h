#pragma once
#include"define.h"
#include"CBattle.h"
#include"CManage.h"
#include"SoundManager.h"


#define PHASE_BATTLE 0
#define PHASE_MANAGE 1

class CInGame {
	const CSoundManager* m_pSoundManager;

	// 제대로 세팅이 넘어왔는지 확인
	bool m_bSet{ false };

	// 페이즈 2개를 번갈아 사용한다.
	CBattle* m_pBattlePhase;
	CManage* m_pManagePhase;
	UINT m_nPhase;

	// 두 페이즈 모두에서 쓰이는 변수
	int m_nGold;
	UINT m_nStage;
	// 플레이어의 상태 (업그레이드 상태)
	// ...
	//CItem* m_pCastle;
	// 배틀페이즈에서 쓰이는 변수
	

public:
	CInGame(const CSoundManager* sound) : m_pSoundManager(sound) {}
	~CInGame();
	// 초기화 해주는 함수
	void Init();

	void MouseMove(const LPARAM& lParam);
	void LButtonDown(const LPARAM& lParam);

	// 키보드 명령 받는 함수
	void GetKey(const WPARAM& wParam);

	// 게임 안에서 그려주는 함수
	void DrawInGame(HDC hdc);;

	// 게임 안 업데이트 함수
	void Update();
};