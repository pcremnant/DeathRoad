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
	// �÷��̾�
	UINT level_PlayerAttack{ 1 };

	// �뺴
	UINT level_ArcherAttack{ 1 };
	UINT level_ArcherRange{ 1 };
	UINT level_ArcherReroad{ 1 };
	UINT level_ArcherNumber{ 0 };

	UINT level_Hp{ 1 };
public:
	// ���׷��̵� �ϴµ� �ʿ��� ���
	int RequiredGold(int nType);

	// ���׷��̵�
	void GetUpgrade(int nType, int* nGold, CCastle* pCastle = nullptr);

	int ReturnUpgradeLevel(int nType);
};