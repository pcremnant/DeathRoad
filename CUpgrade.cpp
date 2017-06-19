#include"CUpgrade.h"

// 업그레이드 하는데 필요한 골드

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
	default:
		break;
	}
	return 0;
}

// 업그레이드

void CUpgrade::GetUpgrade(int nType, int* nGold)
{
	if (nGold - RequiredGold(nType) >= 0)
		nGold -= RequiredGold(nType);
	else return;

	switch (nType) {
	case UPGRADE_PLAYER_ATTACK:
		if (level_PlayerAttack < MAX_LEVEL) {
			level_PlayerAttack++;
		}
		break;
	case UPGRADE_ARCHER_ATTACK:
		if (level_ArcherAttack < MAX_LEVEL) {
			level_ArcherAttack * 100;
		}
		break;
	case UPGRADE_ARCHER_RANGE:
		if (level_ArcherRange < MAX_LEVEL) {
			level_ArcherRange * 150;
		}
		break;
	case UPGRADE_ARCHER_REROAD:
		if (level_ArcherReroad < MAX_LEVEL) {
			level_ArcherReroad * 300;
		}
		break;
	case UPGRADE_CASTLE_HP:
		if (level_Hp < MAX_LEVEL) {
			level_Hp * 200;
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
	default:
		break;
	}
	return 0;
}
