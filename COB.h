
#pragma once
#include<Windows.h>
#include<iostream>
#include<math.h>
#ifndef __CBO_H_
#define __CBO_H_
#define GRAVITY -9.8
#define CHARACTERLEFT 1150
#define CHARACTERTOP 590
#define ENEMYLEFT 1
#define ENEMYTOP 1
typedef struct Plus {
	int WallUpgrade;
	int PlayerUpgrade;
	int Stage;
}pls;
pls STAGE;
class CObject {
protected:
	RECT Mv_obj;
	int Mv_speed;
	BOOL Attack;

public:
	virtual void MF_Move();
	virtual void MF_DrawObj(HDC hdc);
	virtual void MF_Attack();
	virtual void MF_Init();
};
class CMainCharacter :public CObject {
	bool Ready;
	int Mv_mx;
	int Mv_my;
	int Z;
	int damage;
	int direction;
public:
	void MF_Move()override;
	void MF_DrawObj(HDC hdc)override;
	void MF_Attack()override;
	void MF_Init()override;


};
class CCHARACTER :public CObject {
protected:
	int MV_Hp;
	int MV_range;
	int MV_damage;
	bool MV_Stop;
public:
	virtual void MF_Death();
};
class CEnemyArcher :public CCHARACTER {
	int Z;
public:

	void MF_Death()override;
	void MF_Move()override;
	void MF_DrawObj(HDC hdc)override;
	void MF_Attack()override;
	void MF_Init()override;

};
class CEnemyWarrior :public CCHARACTER {
	int Z;
	int MV_Shield;
public:
	void MF_Death()override;
	void MF_Move()override;
	void MF_DrawObj(HDC hdc)override;
	void MF_Attack()override;
	void MF_Init()override;
};
class CWall :public CCHARACTER {
public:
	void MF_Death()override;
	void MF_Init()override;
	void MF_DrawObj(HDC hdc)override;

}cwall;
class CArrow :public CObject {
	int Z;
public:
	void MF_Move()override;
	void MF_DrawObj(HDC hdc)override;
};
#endif