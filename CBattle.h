#pragma once
#include"define.h"
#include"CCastle.h"
#include"CEnemyManager.h"
#include"SoundManager.h"

#define BATTLE_EXIT -1
#define	BATTLE_NONE 0

class CBattle {

	// �ý��� ����
	bool m_bPause{ false };


	// ���� �Ŵ���
	CSoundManager* m_pSoundManager;

	// ��׶��� �̹���
	CImage m_imgBGBack;
	CImage m_imgBGFront;

	// ������ �����Ǵ� �ð��� ��� ����

	UINT m_nTimer;

	// �� ������Ʈ��
	// �Ŵ����� ������ ��
	CEnemyManager* m_pEnemyManager;

	// �÷��̾� ������Ʈ��
	CItem* m_pCastle;


public:
	CBattle(const UINT& nStage, int& nGold, CItem* castle,CSoundManager* sound);
	~CBattle();

	void DrawPhase(HDC hdc);
	void UpdatePhase();
	int GetKey(const WPARAM& wParam);
};