#include"CInGame.h"

// Ű���� ��� �޴� �Լ�


// �ʱ�ȭ ���ִ� �Լ�

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
	m_pUpgrade = new CUpgrade;
	m_nStage = 1;
	m_nGold = 0;
	m_nPhase = PHASE_MANAGE;
	m_pManagePhase = new CManage(m_pSoundManager, &m_nStage, m_pUpgrade, &m_nGold);
	m_bSet = true;
	m_pCastle = new CCastle(500, 500);							// �Ŀ��� ������ ���°� ����
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

// ���� �ȿ��� �׷��ִ� �Լ�

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

// ���� �� ������Ʈ �Լ�

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

// �� Phase�� ����

void CInGame::SetManagePhase()
{
	m_nPhase = PHASE_MANAGE;

	delete m_pBattlePhase;
	m_pBattlePhase = nullptr;

	delete m_pArrow;
	m_pArrow = nullptr;

	m_pManagePhase = new CManage(m_pSoundManager, &m_nStage, m_pUpgrade, &m_nGold);
}

void CInGame::SetBattlePhase()
{
	m_nPhase = PHASE_BATTLE;
	// �Ŵ���������� �ߴ� �ൿ�� ����
	delete m_pManagePhase;
	m_pManagePhase = nullptr;
	m_pArrow = new CPlayerArrowManager(m_pSoundManager);
	dynamic_cast<CMainCharacter*>(m_pPlayer)->SetArrowManager(m_pArrow);
	m_pBattlePhase = new CBattle(m_nStage, m_nGold, m_pCastle, m_pSoundManager, m_pUpgrade, m_pArcher, m_nNumArcher, m_pPlayer, m_pArrow);
}
