#pragma once
#include"define.h"
#include"SoundManager.h"
#include"CEnemyManager.h"

class CIntro {
	CEnemyManager* m_pEnemyManager{ nullptr };
	CSoundManager* m_pSound{ nullptr };
	CItem* m_pCastle{ nullptr };

	// ��׶��� �̹���
	CImage m_imgBGBack;
	CImage m_imgBGFront;
public:
	CIntro();
	~CIntro();

	void Update();

	void DrawIntro(HDC hdc);
};