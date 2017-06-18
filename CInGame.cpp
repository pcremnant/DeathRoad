#include"CInGame.h"

// 키보드 명령 받는 함수


// 초기화 해주는 함수

CInGame::CInGame(CSoundManager* sound) : m_pSoundManager(sound) 
{
	m_pArrow = new CPlayerArrowManager(sound);
	m_pPlayer = new CMainCharacter(m_pSoundManager, m_pArrow);
	m_pPlayer->Init();
}

CInGame::~CInGame()
{
	if (m_pBattlePhase)
		delete m_pBattlePhase;
	if (m_pManagePhase)
		delete m_pManagePhase;
	if (m_pCastle)
		delete m_pCastle;
}

void CInGame::Init()
{
	m_nStage = 1;
	m_nGold = 0;
	m_nPhase = PHASE_MANAGE;
	m_pManagePhase = new CManage(m_pSoundManager);
	m_bSet = true;
	m_pCastle = new CCastle(500, 500);							// 후에는 이전의 상태가 저장
	m_pCastle->Init();
}

void CInGame::MouseMove(const LPARAM & lParam)
{
	if (!m_bSet)return;

	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase) {
			m_pBattlePhase->MouseMove(lParam);
		}
	}
	else if (m_nPhase == PHASE_MANAGE) {
		if (m_pManagePhase)
			m_pManagePhase->MouseMove(lParam);
	}
}

int CInGame::LButtonDown(const LPARAM & lParam)
{
	if (!m_bSet)return INGAME_NONE;

	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase)
			m_pBattlePhase->LButtonDown(lParam);
	}
	else if (m_nPhase == PHASE_MANAGE) {
		if (m_pManagePhase) {
			switch (m_pManagePhase->LButtonDown(lParam)) {
			case MANAGE_NONE:
				break;
			case MANAGE_EXIT:
				delete m_pManagePhase;
				m_pManagePhase = nullptr;
				if (m_pBattlePhase)
					delete m_pBattlePhase;
				m_pBattlePhase = nullptr;
				return INGAME_EXIT;
				break;
			case MANAGE_BATTLESTART:
				SetBattlePhase();
				break;
			default:
				break;
			}
		}
	}

	return INGAME_NONE;
}

void CInGame::LButtonUp(const LPARAM & lParam)
{
	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase)
			m_pBattlePhase->LButtonUp(lParam);
	}
}

void CInGame::GetKey(const WPARAM & wParam)
{
	if (!m_bSet)return;

	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase) {
			switch (m_pBattlePhase->GetKey(wParam)) {
			case BATTLE_EXIT:
				SetManagePhase();
				break;
			case BATTLE_NONE:
				break;
			}
		}
	}
	else if (m_nPhase == PHASE_MANAGE) {
		if (m_pManagePhase)
			m_pManagePhase->GetKey(wParam);
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
	if (m_bSet) {
		if (m_nPhase == PHASE_BATTLE) {
			if (m_pBattlePhase)
				m_pBattlePhase->DrawPhase(hdc);
		}
		else {
			if (m_pManagePhase)
				m_pManagePhase->DrawPhase(hdc);
		}
	}
}

// 게임 안 업데이트 함수

void CInGame::Update()
{
	if (m_bSet) {
		if (m_nPhase == PHASE_BATTLE) {
			if (m_pBattlePhase) {
				m_pBattlePhase->UpdatePhase();
				if (m_pBattlePhase->IsBattleEnd()) {
					SetManagePhase();
				}
			}
		}
		else {
			if (m_pManagePhase)
				;// ManagePhase Update
		}
	}
}
