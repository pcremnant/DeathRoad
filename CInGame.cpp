#include"CInGame.h"

// Ű���� ��� �޴� �Լ�


// �ʱ�ȭ ���ִ� �Լ�

CInGame::~CInGame()
{
	if (m_pBattlePhase)
		delete m_pBattlePhase;
	if (m_pManagePhase)
		delete m_pManagePhase;
	//if (m_pCastle)
		//delete m_pCastle;
}

void CInGame::Init()
{
	m_nStage = 1;
	m_nGold = 0;
	m_nPhase = PHASE_BATTLE;
//	m_pCastle = new CCastle();
	//m_pCastle->Init();
	m_pBattlePhase = new CBattle(m_nStage, m_nGold, 0);
	m_bSet = true;
}

void CInGame::GetKey(const WPARAM & wParam)
{
	if (!m_bSet)return;

	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase)
			m_pBattlePhase->GetKey(wParam);
	}
	else if (m_nPhase == PHASE_MANAGE) {
		if (m_pManagePhase)
			;// MANAGE PHASE GETKEY
	}
	else {
		switch (wParam) {


		default:
			break;
		}
	}
}

// ���� �ȿ��� �׷��ִ� �Լ�

void CInGame::DrawInGame(HDC hdc) {
	if (m_bSet) {
		if (m_nPhase == PHASE_BATTLE) {
			if (m_pBattlePhase)
				m_pBattlePhase->DrawPhase(hdc);
		}
		else {
			if (m_pManagePhase)
				;// ManagePhase Draw
		}
	}
}

// ���� �� ������Ʈ �Լ�

void CInGame::Update()
{
	if (m_bSet) {
		if (m_nPhase == PHASE_BATTLE) {
			if (m_pBattlePhase)
				m_pBattlePhase->UpdatePhase();
		}
		else {
			if (m_pManagePhase)
				;// ManagePhase Update
		}
	}
}
