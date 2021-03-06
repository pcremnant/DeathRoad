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
	if (m_pUpgrade)
		delete m_pUpgrade;
	if (m_pBattlePhase)
		delete m_pBattlePhase;
	if (m_pManagePhase)
		delete m_pManagePhase;
	if (m_pCastle)
		delete m_pCastle;
}

void CInGame::Init()
{
	m_pCastle = new CCastle(500, 500);							// 후에는 이전의 상태가 저장
	m_pCastle->Init();
	m_pUpgrade = new CUpgrade;
	m_nStage = 1;
	m_nGold = 10000;
	m_nPhase = PHASE_MANAGE;
	m_pManagePhase = new CManage(m_pSoundManager, &m_nStage, m_pUpgrade, &m_nGold, m_pCastle);
	m_bSet = true;
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
			case MANAGE_NEXTSTAGE:
				if (m_nStage < 10)
					m_nStage++;
				break;
			case MANAGE_PREVSTAGE:
				if (m_nStage > 1)
					m_nStage--;
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
				if (m_pBattlePhase->IsGameOver()) {
					
					if (m_pBattlePhase)
						delete m_pBattlePhase;
					m_pBattlePhase = nullptr;
					//return INGAME_EXIT;
					if(m_pManagePhase)
						delete m_pManagePhase;
					m_pManagePhase = nullptr;
					m_bGameOver = true;
					// 게임 종료
				}
				else if (m_pBattlePhase->IsBattleEnd()) {
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

// 각 Phase를 세팅

void CInGame::SetManagePhase()
{
	m_nPhase = PHASE_MANAGE;

	delete m_pBattlePhase;
	m_pBattlePhase = nullptr;

	delete m_pArrow;
	m_pArrow = nullptr;

	for (int i = 0;i < m_nNumArcher;++i)
		delete m_pArcher[i];
	delete m_pArcher;
	m_pArcher = nullptr;

	m_pManagePhase = new CManage(m_pSoundManager, &m_nStage, m_pUpgrade, &m_nGold, m_pCastle);
}

void CInGame::SetBattlePhase()
{
	m_nPhase = PHASE_BATTLE;
	// 매니지페이즈에서 했던 행동들 저장
	delete m_pManagePhase;
	m_pManagePhase = nullptr;
	m_pArrow = new CPlayerArrowManager(m_pSoundManager);
	dynamic_cast<CMainCharacter*>(m_pPlayer)->SetArrowManager(m_pArrow);
	dynamic_cast<CMainCharacter*>(m_pPlayer)->SetUpgrade(m_pUpgrade);

	m_nNumArcher = m_pUpgrade->ReturnUpgradeLevel(UPGRADE_ARCHER_ADD);
	if (m_nNumArcher > 0) {
		m_pArcher = new CObject*[m_nNumArcher];
		for (int i = 0;i < m_nNumArcher;++i) {
			m_pArcher[i] = new CPlayerArcher(m_pSoundManager, m_pArrow, m_pUpgrade);
			m_pArcher[i]->Init();
		}
	}

	m_pBattlePhase = new CBattle(m_nStage, m_nGold, m_pCastle, m_pSoundManager, m_pUpgrade, m_pArcher, m_nNumArcher, m_pPlayer, m_pArrow);
}
