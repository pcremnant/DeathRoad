#include"CManage.h"

CManage::CManage(CSoundManager * sound, UINT* pStage, CUpgrade* pUpgrade, int* pGold) : m_pSoundManager(sound), m_pStage(pStage), m_pUpgrade(pUpgrade),m_pGold(pGold) {
	
	m_spBG.GetImage(TEXT("resource/image/stage/Manage_Background.png"), RECT{ 0,0,CLIENT_WIDTH,CLIENT_HEIGHT });
	m_spGroupPlayer.GetImage(TEXT("resource/image/Icon/Icon_Group_Player.png"), RECT{ 100,50,350,150 });
	m_spGroupArcher.GetImage(TEXT("resource/image/Icon/Icon_Group_Archer.png"), RECT{ 800,50,1050,150 });

	m_spIcon[ICON_EXIT].GetImage(TEXT("resource/image/Icon/Icon_ExitButton.png"), RECT{ 50,520,250,570 }, TEXT("resource/image/Icon/Icon_ExitButton_Pointed.png"));
	m_spIcon[ICON_BATTLESTART].GetImage(TEXT("resource/image/Icon/Icon_StartButton.png"), RECT{ 950,520,1150,570 }, TEXT("resource/image/Icon/Icon_StartButton_Pointed.png"));
	
	m_spIcon[ICON_NEXTSTAGE].GetImage(TEXT("resource/image/Icon/Icon_NextStage.png"), RECT{ 650,520,700,570 }, TEXT("resource/image/Icon/Icon_NextStage_Pointed.png"));
	m_spIcon[ICON_PREVSTAGE].GetImage(TEXT("resource/image/Icon/Icon_PrevStage.png"), RECT{ 500,520,550,570 }, TEXT("resource/image/Icon/Icon_PrevStage_Pointed.png"));

	m_spIcon[ICON_UPGRADE_PLAYER_DAMAGE].GetImage(TEXT("resource/image/Icon/Icon_Player_Damage.png"), RECT{ 100,220,150,270 });
	m_spIcon[ICON_UPGRADE_PLAYER_DAMAGEUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 260,220,310,270 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_CASTLE_HP].GetImage(TEXT("resource/image/Icon/Icon_Castle_Hp.png"), RECT{ 100,300,150,350 });
	m_spIcon[ICON_UPGRADE_CASTLE_HPUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 260,300,310,350 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_CASTLE_REPAIR].GetImage(TEXT("resource/image/Icon/Icon_Castle_Repair.png"), RECT{ 100,380,150,430 });
	m_spIcon[ICON_UPGRADE_CASTLE_REPAIRUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 260,380,310,430 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));


	m_spIcon[ICON_UPGRADE_ARCHER_DAMAGE].GetImage(TEXT("resource/image/Icon/Icon_Archer_Damage.png"), RECT{ 800,220,850,270 });
	m_spIcon[ICON_UPGRADE_ARCHER_DAMAGEUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 960,220,1010,270 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_ARCHER_RANGE].GetImage(TEXT("resource/image/Icon/Icon_Archer_Range.png"), RECT{ 800,300,850,350 });
	m_spIcon[ICON_UPGRADE_ARCHER_RANGEUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 960,300,1010,350 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_ARCHER_REROAD].GetImage(TEXT("resource/image/Icon/Icon_Archer_Speed.png"), RECT{ 800,380,850,430 });
	m_spIcon[ICON_UPGRADE_ARCHER_REROADUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 960,380,1010,430 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_GOLD].GetImage(TEXT("resource/image/Icon/Icon_Money.png"), RECT{ 1100,0,1150,50 });

}

CManage::~CManage()
{
	
}

void CManage::MouseMove(const LPARAM & lParam)
{
	for (int i = 0;i < ICON_NUMBER;++i)
		m_spIcon[i].InMouse(lParam);
}

int CManage::LButtonDown(const LPARAM & lParam)
{
	if (m_spIcon[ICON_BATTLESTART].GetPointed())
		return MANAGE_BATTLESTART;
	else if (m_spIcon[ICON_EXIT].GetPointed())
		return MANAGE_EXIT;
	else if (m_spIcon[ICON_NEXTSTAGE].GetPointed())
		return MANAGE_NEXTSTAGE;
	else if (m_spIcon[ICON_PREVSTAGE].GetPointed())
		return MANAGE_PREVSTAGE;
	else if (m_spIcon[ICON_UPGRADE_PLAYER_DAMAGEUP].GetPointed()) {
		if (*m_pGold >= m_pUpgrade->RequiredGold(UPGRADE_PLAYER_ATTACK)) {
			m_pUpgrade->GetUpgrade(UPGRADE_PLAYER_ATTACK, m_pGold);
		}
	}
	else
		return MANAGE_NONE;
}

void CManage::DrawPhase(HDC hdc)
{
	m_spBG.DrawSprite(hdc);
	for (int i = 0;i < ICON_NUMBER;++i) {
		if (i == ICON_GOLD) {
			Rectangle(hdc, 1100, 0, 1200, 50);
			m_spIcon[i].DrawSprite(hdc, true);
			TCHAR strTmp[10];
			wsprintf(strTmp, TEXT("%d"), *m_pGold);
			RECT rcTmp = { 1150,0,1200,50 };
			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else
			m_spIcon[i].DrawSprite(hdc);
	}



	m_spGroupArcher.DrawSprite(hdc, true);
	m_spGroupPlayer.DrawSprite(hdc, true);

	Rectangle(hdc, 550, 520, 650, 570);

	HFONT hFont, oldFont;
	hFont = CreateFont(50, 0, 0, 0, 4, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("±¼¸²"));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	SetBkColor(hdc, RGB(255, 255, 255));
	TCHAR strStage[4];
	wsprintf(strStage, TEXT("%d"), *m_pStage);
	RECT rcTmp = { 450,522,750,568 };
	DrawText(hdc, strStage, -1, &rcTmp, DT_CENTER | DT_VCENTER);
	SelectObject(hdc,oldFont);
	DeleteObject(hFont);
}
