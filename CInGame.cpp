#include"CInGame.h"

// 키보드 명령 받는 함수


// 초기화 해주는 함수

CInGame::CInGame(CSoundManager* sound) : m_pSoundManager(sound) {}

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
	m_pCastle = new CCastle();
	m_pCastle->Init();
}

void CInGame::MouseMove(const LPARAM & lParam)
{
	if (!m_bSet)return;

	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase)
			;
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
			;
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
				m_nPhase = PHASE_BATTLE;
				// 매니지페이즈에서 했던 행동들 저장
				delete m_pManagePhase;
				m_pManagePhase = nullptr;
				m_pBattlePhase = new CBattle(m_nStage, m_nGold, m_pCastle, m_pSoundManager);
				break;
			default:
				break;
			}
		}
	}

	return INGAME_NONE;
}

void CInGame::GetKey(const WPARAM & wParam)
{
	if (!m_bSet)return;

	if (m_nPhase == PHASE_BATTLE) {
		if (m_pBattlePhase) {
			switch (m_pBattlePhase->GetKey(wParam)) {
			case BATTLE_EXIT:
				m_nPhase = PHASE_MANAGE;
				// 배틀페이즈에서 했던 행동들 저장
				delete m_pBattlePhase;
				m_pBattlePhase = nullptr;
				m_pManagePhase = new CManage(m_pSoundManager);
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
			if (m_pBattlePhase)
				m_pBattlePhase->UpdatePhase();
		}
		else {
			if (m_pManagePhase)
				;// ManagePhase Update
		}
	}
}
