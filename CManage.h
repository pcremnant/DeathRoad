#pragma once
#include"define.h"
#include"CSprite.h"
#include"SoundManager.h"

// LButtonDown���� �Ѱ��ִ� ���ڰ�

#define MANAGE_NONE 0
#define MANAGE_EXIT 1000
#define MANAGE_BATTLESTART 1001
#define MANAGE_NEXTSTAGE 1002
#define MANAGE_PREVSTAGE 1003

#define ICON_NUMBER 4
// ������ ������ȣ
#define ICON_EXIT 0
#define ICON_BATTLESTART 1
#define ICON_NEXTSTAGE 2
#define ICON_PREVSTAGE 3

class CManage {
	// �Ŵ��� ��� �̹���
	CSprite m_spBG;
	CSprite m_spIcon[ICON_NUMBER];
	
	CSoundManager* m_pSoundManager;

	UINT* m_pStage{ nullptr };
	//CImage m_imgBG;							// ��� �̹���
	//CImage m_imgIcon[ICON_NUMBER];			// ������ �̹��� - ���� �����ΰ����� �д´�.
	//RECT m_rcIcon[ICON_NUMBER];				// ������ ��ġ - ���� ���� �����ΰ����� �д´�.


public:
	CManage(CSoundManager* sound, UINT* pStage);
	~CManage();

	void MouseMove(const LPARAM& lParam);
	int LButtonDown(const LPARAM& lParam);
	void DrawPhase(HDC hdc);
	void GetKey(const WPARAM& wParam) {};
};