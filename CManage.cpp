#include"CManage.h"

CManage::CManage(CSoundManager * sound) : m_pSoundManager(sound) {
	m_spBG.GetImage(TEXT("resource/image/stage/Manage_Background.png"), RECT{ 0,0,CLIENT_WIDTH,CLIENT_HEIGHT });
	m_spIcon[ICON_EXIT].GetImage(TEXT("resource/image/Icon/Icon_ExitButton.png"), RECT{ 50,520,250,570 }, TEXT("resource/image/Icon/Icon_ExitButton_Pointed.png"));
	m_spIcon[ICON_BATTLESTART].GetImage(TEXT("resource/image/Icon/Icon_StartButton.png"), RECT{ 950,520,1150,570 }, TEXT("resource/image/Icon/Icon_StartButton_Pointed.png"));
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
	else
		return MANAGE_NONE;

}

void CManage::DrawPhase(HDC hdc)
{
	m_spBG.DrawSprite(hdc);
	for (int i = 0;i < ICON_NUMBER;++i)
		m_spIcon[i].DrawSprite(hdc);
}
