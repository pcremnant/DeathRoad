#pragma once
#include"define.h"
#include"CCastle.h"
#include"CEnemyManager.h"
#include"SoundManager.h"
#include"CEnemyArrowManager.h"
#include"CPlayerArrowManager.h"
#include"CPlayerArcher.h"
#include"CUpgrade.h"
#include"CMainCharacter.h"

#define BATTLE_EXIT -1
#define	BATTLE_NONE 0

class CBattle {

	// �ý��� ����
	bool m_bPause{ false };
	bool m_bBattleEnd{ false };

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
	CPlayerArrowManager* m_pArrowManager;
	CObject** m_pArcher;
	UINT m_nNumArcher{ 0 };					// �뺴 �ü����� ����

	// �÷��̾� ������Ʈ��
	CItem* m_pCastle;
	CObject* m_pPlayer;


public:
	CBattle(const UINT& nStage, int& nGold, CItem* castle,CSoundManager* sound, CUpgrade* upgrade, CObject** pArcher, const int& nNumArcher, CObject* player);
	~CBattle();

	void DrawPhase(HDC hdc);
	void UpdatePhase();
	int GetKey(const WPARAM& wParam);
	int LButtonUp(const LPARAM& lParam);
	void LButtonDown(const LPARAM& lParam);
	void MouseMove(const LPARAM& lParam);
	bool IsBattleEnd() const;
};