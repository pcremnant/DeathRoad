#pragma once
#include"define.h"
#include"CCastle.h"
#include"CEnemyManager.h"
#include"SoundManager.h"
#include"CEnemyArrowManager.h"
#include"CPlayerArrowManager.h"
#include"CPlayerArcher.h"
#include"CUpgrade.h"
#include"CMainCharacter.h"

#define BATTLE_EXIT -1
#define	BATTLE_NONE 0

class CBattle {

	// 시스템 변수
	bool m_bPause{ false };
	bool m_bBattleEnd{ false };
	bool m_bGameOver{ false };
	// 사운드 매니저
	CSoundManager* m_pSoundManager;

	// 백그라운드 이미지
	CImage m_imgBGBack;
	CImage m_imgBGFront;

	// 적군이 생성되는 시간을 재는 변수
	UINT m_nTimer;
	// 매니저로 관리할 것
	CEnemyManager* m_pEnemyManager;
	CPlayerArrowManager* m_pArrowManager;
	CObject** m_pArcher;
	UINT m_nNumArcher{ 0 };					// 용병 궁수들의 숫자

	// 플레이어 오브젝트들
	CItem* m_pCastle;
	CObject* m_pPlayer;

	UINT m_nGetGold{ 0 };
	int* m_pGold{ nullptr };
public:
	CBattle(const UINT& nStage, int& nGold, CItem* castle,CSoundManager* sound, CUpgrade* upgrade, CObject** pArcher, const int& nNumArcher, CObject* player, CPlayerArrowManager* arrowManager);
	~CBattle();

	void DrawPhase(HDC hdc);
	void UpdatePhase();
	int GetKey(const WPARAM& wParam);
	int LButtonUp(const LPARAM& lParam);
	void LButtonDown(const LPARAM& lParam);
	void MouseMove(const LPARAM& lParam);
	bool IsBattleEnd() const;
	bool IsGameOver() const
	{
		return m_bGameOver;
	}
};