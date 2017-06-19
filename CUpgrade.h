#pragma once
#include"define.h"
#include"CCastle.h"

#define UPGRADE_PLAYER_ATTACK 0

#define UPGRADE_ARCHER_ATTACK 1
#define UPGRADE_ARCHER_RANGE 2
#define UPGRADE_ARCHER_REROAD 3
#define UPGRADE_ARCHER_ADD 6

#define UPGRADE_CASTLE_HP 4
#define UPGRADE_CASTLE_REPAIR 5
#define MAX_LEVEL 8

class CUpgrade {
	// 플레이어
	UINT level_PlayerAttack{ 1 };

	// 용병
	UINT level_ArcherAttack{ 1 };
	UINT level_ArcherRange{ 1 };
	UINT level_ArcherReroad{ 1 };
	UINT level_ArcherNumber{ 0 };

	UINT level_Hp{ 1 };
public:
	// 업그레이드 하는데 필요한 골드
	int RequiredGold(int nType);

	// 업그레이드
	void GetUpgrade(int nType, int* nGold, CCastle* pCastle = nullptr);

	int ReturnUpgradeLevel(int nType);
};