#include"CUpgrade.h"

// ���׷��̵� �ϴµ� �ʿ��� ���

int CUpgrade::RequiredGold(int nType)
{
	switch (nType) {
	case UPGRADE_PLAYER_ATTACK:
		return level_PlayerAttack * 100;
		break;
	case UPGRADE_ARCHER_ATTACK:
		return level_ArcherAttack * 100;
		break;
	case UPGRADE_ARCHER_RANGE:
		return level_ArcherRange * 150;
		break;
	case UPGRADE_ARCHER_REROAD:
		return level_ArcherReroad * 300;
		break;
	case UPGRADE_CASTLE_HP:
		return level_Hp * 200;
		break;
	case UPGRADE_CASTLE_REPAIR:
		return 50;
		break;
	case UPGRADE_ARCHER_ADD:
		return (level_ArcherNumber+1) * 150;
		break;
	default:
		break;
	}
	return 0;
}

// ���׷��̵�

void CUpgrade::GetUpgrade(int nType, int* nGold, CCastle* pCastle)
{
	if (*nGold - RequiredGold(nType) >= 0 && ReturnUpgradeLevel(nType) < MAX_LEVEL)
		*nGold -= RequiredGold(nType);
	else return;

	switch (nType) {
	case UPGRADE_PLAYER_ATTACK:
		if (level_PlayerAttack < MAX_LEVEL) {
			level_PlayerAttack++;
		}
		break;
	case UPGRADE_ARCHER_ATTACK:
		if (level_ArcherAttack < MAX_LEVEL) {
			level_ArcherAttack++;
		}
		break;
	case UPGRADE_ARCHER_RANGE:
		if (level_ArcherRange < MAX_LEVEL) {
			level_ArcherRange++;
		}
		break;
	case UPGRADE_ARCHER_REROAD:
		if (level_ArcherReroad < MAX_LEVEL) {
			level_ArcherReroad++;
		}
		break;
	case UPGRADE_CASTLE_HP:
		if (level_Hp < MAX_LEVEL) {
			level_Hp++;
			pCastle->SetMaxHp(500 * level_Hp);
		}
		break;
	case UPGRADE_CASTLE_REPAIR:
		if (pCastle && pCastle->ReturnMaxHp() > pCastle->ReturnHp()) {
			pCastle->SetHp(pCastle->ReturnMaxHp());
		}
		break;
	case UPGRADE_ARCHER_ADD:
		if (level_ArcherNumber < 20) {
			level_ArcherNumber++;
		}
		break;
	default:
		break;
	}
}

int CUpgrade::ReturnUpgradeLevel(int nType)
{
	switch (nType) {
	case UPGRADE_PLAYER_ATTACK:
		return level_PlayerAttack;
		break;
	case UPGRADE_ARCHER_ATTACK:
		return level_ArcherAttack;
		break;
	case UPGRADE_ARCHER_RANGE:
		return level_ArcherRange;
		break;
	case UPGRADE_ARCHER_REROAD:
		return level_ArcherReroad;
		break;
	case UPGRADE_CASTLE_HP:
		return level_Hp;
		break;
	case UPGRADE_CASTLE_REPAIR:
		return 1;
		break;
	case UPGRADE_ARCHER_ADD:
		return level_ArcherNumber;
		break;
	default:
		break;
	}
	return 0;
}
