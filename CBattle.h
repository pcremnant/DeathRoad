#pragma once
#include"define.h"
#include"CCastle.h"
#include"CEnemyManager.h"
#include"SoundManager.h"
#include"CEnemyArrowManager.h"

#define BATTLE_EXIT -1
#define	BATTLE_NONE 0

class CBattle {

	// 시스템 변수
	bool m_bPause{ false };
	bool m_bBattleEnd{ false };

	// 사운드 매니저
	CSoundManager* m_pSoundManager;

	// 백그라운드 이미지
	CImage m_imgBGBack;
	CImage m_imgBGFront;

	// 적군이 생성되는 시간을 재는 변수

	UINT m_nTimer;

	// 적 오브젝트들
	// 매니저로 관리할 것
	CEnemyManager* m_pEnemyManager;
	// 플레이어 오브젝트들
	CItem* m_pCastle;


public:
	CBattle(const UINT& nStage, int& nGold, CItem* castle,CSoundManager* sound);
	~CBattle();

	void DrawPhase(HDC hdc, CObject* player);
	void UpdatePhase();
	int GetKey(const WPARAM& wParam, CObject* player);
	int LButtonUp(const LPARAM& lParam, CObject* player);
	void LButtonDown(const LPARAM& lParam, CObject* player);
	void MouseMove(const LPARAM& lParam, CObject* player);
	bool IsBattleEnd() const;
};