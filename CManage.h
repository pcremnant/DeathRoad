#pragma once
#include"define.h"
#include"CSprite.h"
#include"SoundManager.h"
#include"CUpgrade.h"

// LButtonDown���� �Ѱ��ִ� ���ڰ�

#define MANAGE_NONE						0
#define MANAGE_EXIT						1000
#define MANAGE_BATTLESTART				1001
#define MANAGE_NEXTSTAGE				1002
#define MANAGE_PREVSTAGE				1003

#define ICON_NUMBER						17

// ������ ������ȣ

#define ICON_EXIT						0			// ����ȭ��
#define ICON_BATTLESTART				1			// ���� ����
#define ICON_NEXTSTAGE					2			// �������� ����
#define ICON_PREVSTAGE					3			// �������� ����

// ���׷��̵� ������
#define ICON_UPGRADE_PLAYER_DAMAGE		4			// �÷��̾� ������ ���׷��̵�
#define ICON_UPGRADE_PLAYER_DAMAGEUP	5			// �÷��̾� ������ ���׷��̵�
#define ICON_UPGRADE_ARCHER_DAMAGE		6			// �ü� ������ ���׷��̵�
#define ICON_UPGRADE_ARCHER_DAMAGEUP	7			// �ü� ������ ���׷��̵�
#define ICON_UPGRADE_ARCHER_RANGE		8			// �ü� ��Ÿ� ���׷��̵�
#define ICON_UPGRADE_ARCHER_RANGEUP		9			// �ü� ��Ÿ� ���׷��̵�
#define ICON_UPGRADE_ARCHER_REROAD		10			// �ü� �����ӵ� ���׷��̵�
#define ICON_UPGRADE_ARCHER_REROADUP	11			// �ü� �����ӵ� ���׷��̵�
#define ICON_UPGRADE_CASTLE_HP			12			// �� ü�� ���׷��̵�
#define ICON_UPGRADE_CASTLE_HPUP		13			// �� ü�� ���׷��̵�
#define ICON_UPGRADE_CASTLE_REPAIR		14			// �� ����
#define ICON_UPGRADE_CASTLE_REPAIRUP	15			// �� ����
#define ICON_GOLD						16			// ��

class CManage {
	// �Ŵ��� ��� �̹���
	CSprite m_spBG;
	CSprite m_spIcon[ICON_NUMBER];
	CSprite m_spGroupPlayer;
	CSprite m_spGroupArcher;

	CSoundManager* m_pSoundManager;
	CUpgrade* m_pUpgrade;
	UINT* m_pStage{ nullptr };
	int* m_pGold{ nullptr };
	//CImage m_imgBG;							// ��� �̹���
	//CImage m_imgIcon[ICON_NUMBER];			// ������ �̹��� - ���� �����ΰ����� �д´�.
	//RECT m_rcIcon[ICON_NUMBER];				// ������ ��ġ - ���� ���� �����ΰ����� �д´�.


public:
	CManage(CSoundManager* sound, UINT* pStage, CUpgrade* pUpgrade, int* pGold);
	~CManage();

	void MouseMove(const LPARAM& lParam);
	int LButtonDown(const LPARAM& lParam);
	void DrawPhase(HDC hdc);
	void GetKey(const WPARAM& wParam) {};
};