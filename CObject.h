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
	// �̹���
	CImage m_imgWalk;
	CImage m_imgAttack;
	CImage m_imgDead;

	// �̹��� �ʱ�ȭ	(�ȱ⵿�� �ּ�, ���ݵ��� �ּ�, �״µ��� �ּ�, �ȱ⵿�� �ִ�������, ���ݵ��� �ִ�������, �״µ��� �ִ�������)
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

	// �̹��� Ÿ��(�ȱ�/����/����)�� ���� �������� �ҷ��� �̹��� ��ġ�� ���Ѵ�.
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
	// �ִ� ������
	int m_nWalkFrame;
	int m_nAttackFrame;
	int m_nDeadFrame;

	// �̹������� �о�� �κ�
	RECT m_rcFramePosition;

	// �̹��� ũ��
	int m_nWalkWidth{ 0 };
	int m_nWalkHeight{ 0 };
	int m_nAttackWidth{ 0 };
	int m_nAttackHeight{ 0 };
	int m_nDeadWidth{ 0 };
	int m_nDeadHeight{ 0 };

};

class CObject {
protected:
	// �̹��� ����
	Sprite m_sprImg;
	int m_nFrameType;
	int m_nFrame{ 0 };

	// ������Ʈ�� ��ġ����
	CVector3D m_vtCoord{ 0,0,0 };		// ��ǥ
	int m_nWidth{ 0 };					// x ũ�� -> �߽� �������� �� �� �������� �Ÿ�
	int m_nHeight{ 0 };					// y ũ�� -> �߽� �������� �� �� �������� �Ÿ�
										// �������� �ٿ���ڽ�(�浹 �ڽ�)						

	RECT m_rcPosition{ 0,0,0,0 };		// ���� �̹����� ������ �簢��

	bool m_bAttackCharge;				// ������ �غ��ϰ� �ִ°�

public:

	virtual void Init() {};								// �ʱ�ȭ ���ִ� �Լ�
	virtual void DrawObject(HDC hdc) {};				// ��ο� �Լ�
	virtual void Move() {};								// Update�� �����̴� �Լ�
	virtual void GetUpgrade() {};						// ��Ʋ������ ���۽� (Ȥ�� ������Ʈ ������) ���׷��̵� ������ �����ش�.
	virtual void SetPosition() {};						// m_vtCoord�� ���� �ٿ�� �ڽ�(�̹��� ��ġ �� ũ��)�� �����ִ� �Լ�
	virtual void SetFrameType(const int& nType) {};		// Ư�� ��Ȳ���� ������ �ٲ��ش�.(�ȴٰ� ��Ÿ� ������ ������ ���� ������� �ٲ���)

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