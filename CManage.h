#pragma once
#include"define.h"
#include"CSprite.h"
#include"SoundManager.h"
#include"CUpgrade.h"

// LButtonDown에서 넘겨주는 인자값

#define MANAGE_NONE						0
#define MANAGE_EXIT						1000
#define MANAGE_BATTLESTART				1001
#define MANAGE_NEXTSTAGE				1002
#define MANAGE_PREVSTAGE				1003

#define ICON_NUMBER						17

// 아이콘 고유번호

#define ICON_EXIT						0			// 메인화면
#define ICON_BATTLESTART				1			// 전투 시작
#define ICON_NEXTSTAGE					2			// 스테이지 조절
#define ICON_PREVSTAGE					3			// 스테이지 조절

// 업그레이드 아이콘
#define ICON_UPGRADE_PLAYER_DAMAGE		4			// 플레이어 데미지 업그레이드
#define ICON_UPGRADE_PLAYER_DAMAGEUP	5			// 플레이어 데미지 업그레이드
#define ICON_UPGRADE_ARCHER_DAMAGE		6			// 궁수 데미지 업그레이드
#define ICON_UPGRADE_ARCHER_DAMAGEUP	7			// 궁수 데미지 업그레이드
#define ICON_UPGRADE_ARCHER_RANGE		8			// 궁수 사거리 업그레이드
#define ICON_UPGRADE_ARCHER_RANGEUP		9			// 궁수 사거리 업그레이드
#define ICON_UPGRADE_ARCHER_REROAD		10			// 궁수 장전속도 업그레이드
#define ICON_UPGRADE_ARCHER_REROADUP	11			// 궁수 장전속도 업그레이드
#define ICON_UPGRADE_CASTLE_HP			12			// 성 체력 업그레이드
#define ICON_UPGRADE_CASTLE_HPUP		13			// 성 체력 업그레이드
#define ICON_UPGRADE_CASTLE_REPAIR		14			// 성 수리
#define ICON_UPGRADE_CASTLE_REPAIRUP	15			// 성 수리
#define ICON_GOLD						16			// 돈

class CManage {
	// 매니지 모드 이미지
	CSprite m_spBG;
	CSprite m_spIcon[ICON_NUMBER];
	CSprite m_spGroupPlayer;
	CSprite m_spGroupArcher;

	CSoundManager* m_pSoundManager;
	CUpgrade* m_pUpgrade;
	UINT* m_pStage{ nullptr };
	int* m_pGold{ nullptr };
	//CImage m_imgBG;							// 배경 이미지
	//CImage m_imgIcon[ICON_NUMBER];			// 아이콘 이미지 - 위의 디파인값으로 읽는다.
	//RECT m_rcIcon[ICON_NUMBER];				// 아이콘 위치 - 역시 위의 디파인값으로 읽는다.


public:
	CManage(CSoundManager* sound, UINT* pStage, CUpgrade* pUpgrade, int* pGold);
	~CManage();

	void MouseMove(const LPARAM& lParam);
	int LButtonDown(const LPARAM& lParam);
	void DrawPhase(HDC hdc);
	void GetKey(const WPARAM& wParam) {};
};