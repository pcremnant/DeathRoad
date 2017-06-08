#pragma once
#include"define.h"
#include"CVector3D.h"

#define GRAVITY -9.8
#define CHARACTERLEFT 1150
#define CHARACTERTOP 590
#define ENEMYLEFT 1
#define ENEMYTOP 1

#define TYPE_WALK 0
#define TYPE_ATTACK 1
#define TYPE_DEAD 2

struct Sprite {
	// 이미지
	CImage m_imgWalk;
	CImage m_imgAttack;
	CImage m_imgDead;

	// 이미지 초기화	(걷기동작 주소, 공격동작 주소, 죽는동작 주소, 걷기동작 최대프레임, 공격동작 최대프레임, 죽는동작 최대프레임)
	void GetImage(LPCTSTR walk, LPCTSTR attack, LPCTSTR dead, const int& walkFrame, const int& attackFrame, const int& deadFrame)
	{
		m_imgWalk.Load(walk);
		m_imgAttack.Load(attack);
		m_imgDead.Load(dead);
		m_nWalkFrame = walkFrame;
		m_nAttackFrame = attackFrame;
		m_nDeadFrame = deadFrame;

		m_nWalkWidth = m_imgWalk.GetWidth()/m_nWalkFrame;
		m_nWalkHeight = m_imgWalk.GetHeight();
		m_nAttackWidth = m_imgAttack.GetWidth() / m_nAttackFrame;
		m_nAttackHeight = m_imgAttack.GetHeight();
		m_nDeadWidth = m_imgDead.GetWidth() / m_nDeadFrame;
		m_nDeadHeight = m_imgDead.GetHeight();
	}

	// 이미지 타입(걷기/공격/죽음)과 현재 프레임을 불러와 이미지 위치를 정한다.
	void DrawObject(HDC hdc, const int& nType, const int& nFrame, const RECT& rcPos)
	{
		if (nFrame > MaxFrame(nType))
			return;

		if (nType == TYPE_WALK) {
			m_rcFramePosition = { m_nWalkWidth*nFrame,0,m_nWalkWidth*(nFrame + 1),m_nWalkHeight };
			m_imgWalk.TransparentBlt(hdc, rcPos, m_rcFramePosition, RGB(255, 255, 255));
		}
		else if (nType == TYPE_ATTACK) {
			m_rcFramePosition = { m_nAttackWidth*nFrame,0,m_nAttackWidth*(nFrame + 1),m_nAttackHeight };
			m_imgAttack.TransparentBlt(hdc, rcPos, m_rcFramePosition, RGB(255, 255, 255));
		}
		else if (nType == TYPE_DEAD) {
			m_rcFramePosition = { m_nDeadWidth*nFrame,0,m_nDeadWidth*(nFrame + 1),m_nDeadHeight };
			m_imgDead.TransparentBlt(hdc, rcPos, m_rcFramePosition, RGB(255, 255, 255));
		}
	}

	const int& MaxFrame(const int& nType) const
	{
		if (nType == TYPE_WALK)
			return m_nWalkFrame;
		else if (nType == TYPE_ATTACK)
			return m_nAttackFrame;
		else if (nType == TYPE_DEAD)
			return m_nDeadFrame;

		return 0;
	}

private:
	// 최대 프레임
	int m_nWalkFrame;
	int m_nAttackFrame;
	int m_nDeadFrame;

	// 이미지에서 읽어올 부분
	RECT m_rcFramePosition;

	// 이미지 크기
	int m_nWalkWidth{ 0 };
	int m_nWalkHeight{ 0 };
	int m_nAttackWidth{ 0 };
	int m_nAttackHeight{ 0 };
	int m_nDeadWidth{ 0 };
	int m_nDeadHeight{ 0 };

};

class CObject {
protected:
	// 이미지 정보
	Sprite m_sprImg;
	int m_nFrameType;
	int m_nFrame{ 0 };

	// 오브젝트의 위치정보
	CVector3D m_vtCoord{ 0,0,0 };		// 좌표
	int m_nWidth{ 0 };					// x 크기 -> 중심 기준으로 좌 우 끝까지의 거리
	int m_nHeight{ 0 };					// y 크기 -> 중심 기준으로 상 하 끝까지의 거리
										// 실질적인 바운딩박스(충돌 박스)						

	RECT m_rcPosition{ 0,0,0,0 };		// 실제 이미지가 나오는 사각형

	bool m_bAttackCharge;				// 공격을 준비하고 있는가

public:

	virtual void Init() {};								// 초기화 해주는 함수
	virtual void DrawObject(HDC hdc) {};				// 드로우 함수
	virtual void Move() {};								// Update시 움직이는 함수
	virtual void GetUpgrade() {};						// 배틀페이즈 시작시 (혹은 오브젝트 생성시) 업그레이드 정보를 정해준다.
	virtual void SetPosition() {};						// m_vtCoord에 따라 바운딩 박스(이미지 위치 및 크기)를 정해주는 함수
	virtual void SetFrameType(const int& nType) {};		// 특정 상황에서 동작을 바꿔준다.(걷다가 사거리 안으로 들어오면 공격 모션으로 바꿔줌)

private:

};

/*
typedef struct Plus {
	int WallUpgrade;
	int PlayerUpgrade;
	int Stage;
}pls;

pls STAGE;

class CObject {
protected:
	RECT m_rcPosition;
	int m_nSpeed;
	BOOL m_bAttackCharge;

public:
	virtual void MF_Move() {};
	virtual void MF_DrawObj(HDC hdc) {};
	virtual void MF_Attack() {};
	virtual void MF_Init() {};
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
	virtual void MF_Death() {};
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
	void MF_Death()override {};
	void MF_Init()override {};
	void MF_DrawObj(HDC hdc)override {};

};

class CArrow :public CObject {
	int Z;
public:
	void MF_Move()override {};
	void MF_DrawObj(HDC hdc)override {};
};*/