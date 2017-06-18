#pragma once
#include"define.h"

#define UPGRADE_PLAYER_ATTACK 0
#define UPGRADE_PLAYER_RANGE 1

#define UPGRADE_ARCHER_ATTACK 2
#define UPGRADE_ARCHER_RANGE 3
#define UPGRADE_ARCHER_REROAD 4

#define UPGRADE_CASTLE_HP 5

#define MAX_LEVEL 8

class CUpgrade {
	// 플레이어
	UINT level_PlayerAttack{ 1 };
	UINT level_PlayerRange{ 1 };

	// 용병
	UINT level_ArcherAttack{ 1 };
	UINT level_ArcherRange{ 1 };
	UINT level_ArcherReroad{ 1 };

	UINT level_Hp{ 1 };
public:
	// 업그레이드 하는데 필요한 골드
	int RequiredGold(int nType);

	// 업그레이드
	void GetUpgrade(int nType, int& nGold);

	int ReturnUpgradeLevel(int nType);
};