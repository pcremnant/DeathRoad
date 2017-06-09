#pragma once
#include"define.h"
#include"CCastle.h"
#include"CEnemyManager.h"
#include"SoundManager.h"

class CBattle {
	// ���� �Ŵ���
	const CSoundManager* m_pSoundManager;

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
	CBattle(const UINT& nStage, int& nGold, const int& nCastleHp, const CSoundManager* sound);;
	~CBattle();

	void DrawPhase(HDC hdc);
	void UpdatePhase();
	void GetKey(const WPARAM& wParam);
};