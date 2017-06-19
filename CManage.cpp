#include"CManage.h"

CManage::CManage(CSoundManager * sound, UINT* pStage, CUpgrade* pUpgrade, int* pGold, CItem* pCastle) : m_pSoundManager(sound), m_pStage(pStage), m_pUpgrade(pUpgrade),m_pGold(pGold),m_pCastle(pCastle) {
	
	m_spBG.GetImage(TEXT("resource/image/stage/Manage_Background.png"), RECT{ 0,0,CLIENT_WIDTH,CLIENT_HEIGHT });
	m_spGroupPlayer.GetImage(TEXT("resource/image/Icon/Icon_Group_Player.png"), RECT{ 100,100,350,200 });
	m_spGroupArcher.GetImage(TEXT("resource/image/Icon/Icon_Group_Archer.png"), RECT{ 800,100,1050,200 });

	m_spIcon[ICON_EXIT].GetImage(TEXT("resource/image/Icon/Icon_ExitButton.png"), RECT{ 50,520,250,570 }, TEXT("resource/image/Icon/Icon_ExitButton_Pointed.png"));
	m_spIcon[ICON_BATTLESTART].GetImage(TEXT("resource/image/Icon/Icon_StartButton.png"), RECT{ 950,520,1150,570 }, TEXT("resource/image/Icon/Icon_StartButton_Pointed.png"));
	
	m_spIcon[ICON_NEXTSTAGE].GetImage(TEXT("resource/image/Icon/Icon_NextStage.png"), RECT{ 650,520,700,570 }, TEXT("resource/image/Icon/Icon_NextStage_Pointed.png"));
	m_spIcon[ICON_PREVSTAGE].GetImage(TEXT("resource/image/Icon/Icon_PrevStage.png"), RECT{ 500,520,550,570 }, TEXT("resource/image/Icon/Icon_PrevStage_Pointed.png"));

	m_spIcon[ICON_UPGRADE_PLAYER_DAMAGE].GetImage(TEXT("resource/image/Icon/Icon_Player_Damage.png"), RECT{ 150,220,200,270 });
	m_spIcon[ICON_UPGRADE_PLAYER_DAMAGEUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 310,220,360,270 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_CASTLE_HP].GetImage(TEXT("resource/image/Icon/Icon_Castle_Hp.png"), RECT{ 150,300,200,350 });
	m_spIcon[ICON_UPGRADE_CASTLE_HPUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 310,300,360,350 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_CASTLE_REPAIR].GetImage(TEXT("resource/image/Icon/Icon_Castle_Repair.png"), RECT{ 150,380,200,430 });
	m_spIcon[ICON_UPGRADE_CASTLE_REPAIRUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 310,380,360,430 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_ARCHER_DAMAGE].GetImage(TEXT("resource/image/Icon/Icon_Archer_Damage.png"), RECT{ 850,220,900,270 });
	m_spIcon[ICON_UPGRADE_ARCHER_DAMAGEUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 1010,220,1060,270 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_ARCHER_RANGE].GetImage(TEXT("resource/image/Icon/Icon_Archer_Range.png"), RECT{ 850,300,900,350 });
	m_spIcon[ICON_UPGRADE_ARCHER_RANGEUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 1010,300,1060,350 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_ARCHER_REROAD].GetImage(TEXT("resource/image/Icon/Icon_Archer_Speed.png"), RECT{ 850,380,900,430 });
	m_spIcon[ICON_UPGRADE_ARCHER_REROADUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 1010,380,1060,430 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));

	m_spIcon[ICON_UPGRADE_ARCHER_ADD].GetImage(TEXT("resource/image/Icon/Icon_Archer_Add.png"), RECT{ 850,460,900,510 });
	m_spIcon[ICON_UPGRADE_ARCHER_ADDUP].GetImage(TEXT("resource/image/Icon/Icon_Upgrade.png"), RECT{ 1010,460,1060,510 }, TEXT("resource/image/Icon/Icon_Upgrade_Pointed.png"));


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
			m_pUpgrade->GetUpgrade(UPGRADE_PLAYER_ATTACK, m_pGold);
	}
	else if (m_spIcon[ICON_UPGRADE_ARCHER_DAMAGEUP].GetPointed()) {
		m_pUpgrade->GetUpgrade(UPGRADE_ARCHER_ATTACK, m_pGold);
	}
	else if (m_spIcon[ICON_UPGRADE_ARCHER_RANGEUP].GetPointed()) {
		m_pUpgrade->GetUpgrade(UPGRADE_ARCHER_RANGE, m_pGold);
	}
	else if (m_spIcon[ICON_UPGRADE_ARCHER_REROADUP].GetPointed()) {
		m_pUpgrade->GetUpgrade(UPGRADE_ARCHER_REROAD, m_pGold);
	}
	else if (m_spIcon[ICON_UPGRADE_ARCHER_ADDUP].GetPointed()) {
		m_pUpgrade->GetUpgrade(UPGRADE_ARCHER_ADD, m_pGold);
	}
	else if (m_spIcon[ICON_UPGRADE_CASTLE_HPUP].GetPointed()) {
		m_pUpgrade->GetUpgrade(UPGRADE_CASTLE_HP, m_pGold, dynamic_cast<CCastle*>(m_pCastle));
	}
	else if (m_spIcon[ICON_UPGRADE_CASTLE_REPAIRUP].GetPointed()) {
		m_pUpgrade->GetUpgrade(UPGRADE_CASTLE_REPAIR, m_pGold,dynamic_cast<CCastle*>(m_pCastle));
	}
	else
		return MANAGE_NONE;
}

void CManage::DrawPhase(HDC hdc)
{
	// 배경 그리기
	m_spBG.DrawSprite(hdc);

	// 성 체력 그리기
	{
		HBRUSH hBrush, oldBrush;
		float fTmp = static_cast<float>(m_pCastle->ReturnValue()) / static_cast<float>(dynamic_cast<CCastle*>(m_pCastle)->ReturnMaxHp());
		if (fTmp > 0.7)
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
		else if (fTmp > 0.3)
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
		else
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		RECT rcTmp = { 20,20,20 + 500 * fTmp,50 };
		FillRect(hdc, &rcTmp, hBrush);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(TRANSPARENT);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		rcTmp = { 20,20,520,50 };
		FrameRect(hdc, &rcTmp, hBrush);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		
		//SetBkColor(hdc, NULL);
		TCHAR strTmp[20];
		wsprintf(strTmp, TEXT("%d / %d"), m_pCastle->ReturnValue(), (dynamic_cast<CCastle*>(m_pCastle)->ReturnMaxHp()));
		rcTmp = { 520,20,620,50 };
		DrawText(hdc, strTmp, -1, &rcTmp, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	//SetBkColor(hdc, RGB(255, 255, 255));

	// 업그레이드 항목들 그리기
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
		switch (i) {
		case ICON_UPGRADE_ARCHER_DAMAGE:
		{
			RECT rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left -= 130;
			rcTmp.right -= 80;

			FillRect(hdc, &rcTmp, NULL);

			TCHAR strTmp[15];
			wsprintf(strTmp, TEXT("DAMAGE %dG"), m_pUpgrade->RequiredGold(UPGRADE_ARCHER_ATTACK));
			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left += 80;
			rcTmp.right += 80;

			FillRect(hdc, &rcTmp, NULL);

			wsprintf(strTmp, TEXT("%d"), m_pUpgrade->ReturnUpgradeLevel(UPGRADE_ARCHER_ATTACK));
			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
			break;
		case ICON_UPGRADE_ARCHER_RANGE:
		{
			RECT rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left -= 130;
			rcTmp.right -= 80;

			FillRect(hdc, &rcTmp, NULL);
			TCHAR strTmp[15];
			wsprintf(strTmp, TEXT("RANGE %dG"), m_pUpgrade->RequiredGold(UPGRADE_ARCHER_RANGE));

			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left += 80;
			rcTmp.right += 80;

			FillRect(hdc, &rcTmp, NULL);

			wsprintf(strTmp, TEXT("%d"), m_pUpgrade->ReturnUpgradeLevel(UPGRADE_ARCHER_RANGE));
			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
			break;
		case ICON_UPGRADE_ARCHER_REROAD:
		{
			RECT rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left -= 130;
			rcTmp.right -= 80;
			FillRect(hdc, &rcTmp, NULL);
			TCHAR strTmp[15];
			wsprintf(strTmp, TEXT("REROAD %dG"), m_pUpgrade->RequiredGold(UPGRADE_ARCHER_REROAD));

			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left += 80;
			rcTmp.right += 80;

			FillRect(hdc, &rcTmp, NULL);

			wsprintf(strTmp, TEXT("%d"), m_pUpgrade->ReturnUpgradeLevel(UPGRADE_ARCHER_REROAD));
			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
			break;
		case ICON_UPGRADE_CASTLE_HP:
		{
			RECT rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left -= 130;
			rcTmp.right -= 80;
			FillRect(hdc, &rcTmp, NULL);
			TCHAR strTmp[15];
			wsprintf(strTmp, TEXT("MAXHP %dG"), m_pUpgrade->RequiredGold(UPGRADE_CASTLE_HP));

			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left += 80;
			rcTmp.right += 80;

			FillRect(hdc, &rcTmp, NULL);

			wsprintf(strTmp, TEXT("%d"), m_pUpgrade->ReturnUpgradeLevel(UPGRADE_CASTLE_HP));
			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
			break;
		case ICON_UPGRADE_CASTLE_REPAIR:
		{
			RECT rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left -= 130;
			rcTmp.right -= 80;
			FillRect(hdc, &rcTmp, NULL);
			TCHAR strTmp[15];
			wsprintf(strTmp, TEXT("REPAIR %dG"), m_pUpgrade->RequiredGold(UPGRADE_CASTLE_REPAIR));

			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
			break;
		case ICON_UPGRADE_PLAYER_DAMAGE:
		{
			RECT rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left -= 130;
			rcTmp.right -= 80;
			FillRect(hdc, &rcTmp, NULL);
			TCHAR strTmp[15];
			wsprintf(strTmp, TEXT("DAMAGE"));
			wsprintf(strTmp, TEXT("DAMAGE %dG"), m_pUpgrade->RequiredGold(UPGRADE_PLAYER_ATTACK));

			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left += 80;
			rcTmp.right += 80;

			FillRect(hdc, &rcTmp, NULL);

			wsprintf(strTmp, TEXT("%d"), m_pUpgrade->ReturnUpgradeLevel(UPGRADE_PLAYER_ATTACK));
			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
			break;
		case ICON_UPGRADE_ARCHER_ADD:
		{
			RECT rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left -= 130;
			rcTmp.right -= 80;
			FillRect(hdc, &rcTmp, NULL);
			TCHAR strTmp[15];
			wsprintf(strTmp, TEXT("HIRE %dG"), m_pUpgrade->RequiredGold(UPGRADE_ARCHER_ADD));

			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rcTmp = m_spIcon[i].GetPosition();
			rcTmp.left += 80;
			rcTmp.right += 80;

			FillRect(hdc, &rcTmp, NULL);

			wsprintf(strTmp, TEXT("%d"), m_pUpgrade->ReturnUpgradeLevel(UPGRADE_ARCHER_ADD));
			DrawText(hdc, strTmp, -1, &rcTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
			break;
		default:
			break;
		}

	}

	m_spGroupArcher.DrawSprite(hdc, true);
	m_spGroupPlayer.DrawSprite(hdc, true);

	Rectangle(hdc, 550, 520, 650, 570);

	HFONT hFont, oldFont;
	hFont = CreateFont(50, 0, 0, 0, 4, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	SetBkColor(hdc, RGB(255, 255, 255));
	TCHAR strStage[4];
	wsprintf(strStage, TEXT("%d"), *m_pStage);
	RECT rcTmp = { 450,522,750,568 };
	DrawText(hdc, strStage, -1, &rcTmp, DT_CENTER | DT_VCENTER);
	SelectObject(hdc,oldFont);
	DeleteObject(hFont);
}
