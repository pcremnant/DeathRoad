#include"CManage.h"

CManage::CManage(CSoundManager * sound, UINT* pStage) : m_pSoundManager(sound), m_pStage(pStage) {
	m_spBG.GetImage(TEXT("resource/image/stage/Manage_Background.png"), RECT{ 0,0,CLIENT_WIDTH,CLIENT_HEIGHT });
	m_spIcon[ICON_EXIT].GetImage(TEXT("resource/image/Icon/Icon_ExitButton.png"), RECT{ 50,520,250,570 }, TEXT("resource/image/Icon/Icon_ExitButton_Pointed.png"));
	m_spIcon[ICON_BATTLESTART].GetImage(TEXT("resource/image/Icon/Icon_StartButton.png"), RECT{ 950,520,1150,570 }, TEXT("resource/image/Icon/Icon_StartButton_Pointed.png"));
	m_spIcon[ICON_NEXTSTAGE].GetImage(TEXT("resource/image/Icon/Icon_NextStage.png"), RECT{ 650,520,700,570 }, TEXT("resource/image/Icon/Icon_NextStage_Pointed.png"));
	m_spIcon[ICON_PREVSTAGE].GetImage(TEXT("resource/image/Icon/Icon_PrevStage.png"), RECT{ 500,520,550,570 }, TEXT("resource/image/Icon/Icon_PrevStage_Pointed.png"));
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
	else
		return MANAGE_NONE;
}

void CManage::DrawPhase(HDC hdc)
{
	m_spBG.DrawSprite(hdc);
	for (int i = 0;i < ICON_NUMBER;++i)
		m_spIcon[i].DrawSprite(hdc);

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
