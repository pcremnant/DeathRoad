#pragma once
#include"define.h"
#include"CVector3D.h"
#include"CAnimatedSprite.h"

#define GRAVITY -9.8
#define CHARACTERLEFT 1150
#define CHARACTERTOP 590
#define ENEMYLEFT 1
#define ENEMYTOP 1

#define START_ATTACK -1

// ������ �� �ִϸ��̼��� �߻��ϴ� ������Ʈ Ŭ����
class CObject {
protected:
	// �̹��� ����
	CAnimatedSprite m_sprImg;
	int m_nFrameType;
	int m_nFrame{ 0 };

	// ������Ʈ�� ��ġ����
	CVector3D m_vtCoord{ 0,0,0 };		// ��ǥ
	int m_nWidth{ 0 };					// x ũ�� -> �߽� �������� �� �� �������� �Ÿ�
	int m_nHeight{ 0 };					// y ũ�� -> �߽� �������� �� �� �������� �Ÿ�
										// �������� �ٿ���ڽ�(�浹 �ڽ�)						

	RECT m_rcPosition{ 0,0,0,0 };		// ���� �̹����� ������ �簢��

	bool m_bInRange;					// ���� ��Ÿ� �ȿ� �ִ°�
	bool m_bAttackCharge;				// ������ �غ��ϰ� �ִ°� (Ȱ ������ ���� �ִ� ��)
	int m_nAttackRange;					// ���� ��Ÿ�

	bool m_bDead;						// ������Ʈ�� �׾��°�
public:

	virtual void Init() {};										// �ʱ�ȭ ���ִ� �Լ�
	virtual void DrawObject(HDC hdc) {};						// ��ο� �Լ�
	virtual int Update() = 0;
	virtual void Move() {};										// Update�� �����̴� �Լ�
	virtual int Attack() = 0;									// Update�� �����ϴ� �Լ�
	virtual void Dead() {}										// Update�� �״� �Լ�
	virtual void GetUpgrade() {};								// ��Ʋ������ ���۽� (Ȥ�� ������Ʈ ������) ���׷��̵� ������ �����ش�.
	virtual void SetPosition() {};								// m_vtCoord�� ���� �ٿ�� �ڽ�(�̹��� ��ġ �� ũ��)�� �����ִ� �Լ�
	virtual void SetFrameType(const int& nType) {};				// Ư�� ��Ȳ���� ������ �ٲ��ش�.(�ȴٰ� ��Ÿ� ������ ������ ���� ������� �ٲ���)
	const float ReturnZ() const { return m_vtCoord.GetZ(); }	// �浹������ ���� z���� ����
	const bool& IsDelete() const { return m_bDead; }			// �׾����� üũ�Ͽ� ����
	const bool& InRange() const { return m_bInRange; }			// ���� ��Ÿ� �ȿ� �ִ���
	void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		if (vtPosition.GetX() - nWidth <= m_vtCoord.GetX() + m_nAttackRange)
			m_bInRange = true;
		else m_bInRange = false;
	}
private:

};