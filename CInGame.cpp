#include"CInGame.h"

// 키보드 명령 받는 함수


// 초기화 해주는 함수

void CInGame::Init()
{
	m_nStage = 1;
	m_nGold = 0;
	m_nPhase = PHASE_BATTLE;
	m_pBattlePhase = new CBattle(m_nStage, m_nGold, 0);
}

void CInGame::GetKey(const WPARAM & wParam)
{
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

// 게임 안에서 그려주는 함수

void CInGame::DrawInGame(HDC hdc) {
	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase)
			m_pBattlePhase->DrawPhase(hdc);
	}
	else {
		if (m_pManagePhase)
			;// ManagePhase Draw
	}
}

// 게임 안 업데이트 함수

void CInGame::Update()
{
	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase)
			m_pBattlePhase->UpdatePhase();
	}
	else {
		if (m_pManagePhase)
			;// ManagePhase Update
	}
}
