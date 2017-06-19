#pragma once
#include"define.h"
#include"SoundManager.h"
#include"CEnemyManager.h"
#include"CPlayerArcher.h"

#define INTRO_ARCHER_NUMBER 6

class CIntro {
	CEnemyManager* m_pEnemyManager{ nullptr };
	CSoundManager* m_pSound{ nullptr };
	CItem* m_pCastle{ nullptr };

	// 백그라운드 이미지
	CImage m_imgBGBack;
	CImage m_imgBGFront;

	// 타이틀 이미지
	CImage m_imgTitle;
	RECT m_rcTitle{ 0, };
	int m_nTitleWidth{ 0 };
	int m_nTitleHeight{ 0 };
	bool m_bFixed{ false };					// 타이틀이 고정되었는가

	CImage m_imgPressAnyKey;
	RECT m_rcPressAnyKey{ 0, };
	int m_nPressWidth{ 0 };
	int m_nPressHeight{ 0 };

	CObject* m_pArcher[INTRO_ARCHER_NUMBER]{ nullptr, };
	int m_nArcherNumber{ INTRO_ARCHER_NUMBER };
	CPlayerArrowManager* m_pArrow{ nullptr };

public:
	CIntro();
	~CIntro();

	void Update();
	void DrawIntro(HDC hdc);
	//const bool& IsFixed();
	bool IsFixed() const
	{
		return m_bFixed;
	}
	void SetFixed()
	{
		m_rcTitle.top = CLIENT_HEIGHT / 2 - 200;
		m_rcTitle.bottom = CLIENT_HEIGHT / 2 - 200 + m_nTitleHeight;
		m_bFixed = true;
	}
private:
	void SetTitle();
};