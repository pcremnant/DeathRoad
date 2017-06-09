#pragma once
#include"define.h"
#include"CCastle.h"
#include"CEnemyManager.h"
#include"SoundManager.h"

class CBattle {
	// 사운드 매니저
	const CSoundManager* m_pSoundManager;

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
	CBattle(const UINT& nStage, int& nGold, const int& nCastleHp, const CSoundManager* sound);;
	~CBattle();

	void DrawPhase(HDC hdc);
	void UpdatePhase();
	void GetKey(const WPARAM& wParam);
};