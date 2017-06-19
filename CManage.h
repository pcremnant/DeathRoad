#pragma once
#include"define.h"
#include"CSprite.h"
#include"SoundManager.h"

// LButtonDown에서 넘겨주는 인자값

#define MANAGE_NONE 0
#define MANAGE_EXIT 1000
#define MANAGE_BATTLESTART 1001
#define MANAGE_NEXTSTAGE 1002
#define MANAGE_PREVSTAGE 1003

#define ICON_NUMBER 4
// 아이콘 고유번호
#define ICON_EXIT 0
#define ICON_BATTLESTART 1
#define ICON_NEXTSTAGE 2
#define ICON_PREVSTAGE 3

class CManage {
	// 매니지 모드 이미지
	CSprite m_spBG;
	CSprite m_spIcon[ICON_NUMBER];
	
	CSoundManager* m_pSoundManager;

	UINT* m_pStage{ nullptr };
	//CImage m_imgBG;							// 배경 이미지
	//CImage m_imgIcon[ICON_NUMBER];			// 아이콘 이미지 - 위의 디파인값으로 읽는다.
	//RECT m_rcIcon[ICON_NUMBER];				// 아이콘 위치 - 역시 위의 디파인값으로 읽는다.


public:
	CManage(CSoundManager* sound, UINT* pStage);
	~CManage();

	void MouseMove(const LPARAM& lParam);
	int LButtonDown(const LPARAM& lParam);
	void DrawPhase(HDC hdc);
	void GetKey(const WPARAM& wParam) {};
};