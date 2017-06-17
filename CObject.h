#pragma once
#include"define.h"
#include"CVector3D.h"
#include"CAnimatedSprite.h"
#include"SoundManager.h"

#define UNIT_NONE 0
#define UNIT_ATTACK -1
#define UNIT_DEAD -2

// ������ �� �ִϸ��̼��� �߻��ϴ� ������Ʈ Ŭ����
class CObject {
protected:
	// �̹��� ����
	CAnimatedSprite m_sprImg;
	int m_nFrameType{ 0 };
	int m_nFrame{ 0 };

	// ������Ʈ�� ��ġ����
	CVector3D m_vtCoord{ 0,0,0 };			// ��ǥ
	int m_nWidth{ 0 };						// x ũ�� -> �߽� �������� �� �� �������� �Ÿ�
	int m_nHeight{ 0 };						// y ũ�� -> �߽� �������� �� �� �������� �Ÿ�
											// �������� �ٿ���ڽ�(�浹 �ڽ�)						

	RECT m_rcPosition{ 0,0,0,0 };			// ���� �̹����� ������ �簢��

	bool m_bInRange{ false };				// ���� ��Ÿ� �ȿ� �ִ°�
	bool m_bAttackCharge{ false };			// ������ �غ��ϰ� �ִ°� (Ȱ ������ ���� �ִ� ��)
	bool m_bReroad{ false };				// ���������ΰ�
	int m_nAttackRange{ 0 };				// ���� ��Ÿ�
	int m_nAttack{ 0 };						// ���ݷ�
	int m_nAttackFrame{ 0 };				// ȿ������ �� ������
	int m_nMaxHp{ 0 };						// �ִ�ü��
	int m_nHp{ 0 };							// ����ü��
	bool m_bDead{ false };					// ������Ʈ�� �׾��°�
	int m_nTargeted{ 0 };					// ���� Ÿ���� �� ��

	CSoundManager* m_pSoundManager{ nullptr };
public:
	CObject(CSoundManager* sound) : m_pSoundManager(sound) {}
	virtual void Init() {};										// �ʱ�ȭ ���ִ� �Լ�
	virtual void DrawObject(HDC hdc) {};						// ��ο� �Լ�
	virtual int Update() = 0;
	virtual void Move() {};										// Update�� �����̴� �Լ�
	virtual int Attack() = 0;									// Update�� �����ϴ� �Լ�
	virtual int Dead() = 0;										// Update�� �״� �Լ�
	virtual void GetUpgrade() {};								// ��Ʋ������ ���۽� (Ȥ�� ������Ʈ ������) ���׷��̵� ������ �����ش�.
	virtual void SetPosition() {};								// m_vtCoord�� ���� �ٿ�� �ڽ�(�̹��� ��ġ �� ũ��)�� �����ִ� �Լ�
	virtual void SetFrameType(const int& nType) {};				// Ư�� ��Ȳ���� ������ �ٲ��ش�.(�ȴٰ� ��Ÿ� ������ ������ ���� ������� �ٲ���)
	const float ReturnZ() const { return m_vtCoord.GetZ(); }	// �浹������ ���� z���� ����
	CVector3D ReturnCoord()const { return m_vtCoord; }			// ��ǥ ����
	RECT ReturnPosition() const { return m_rcPosition; }		// �簢�� ����
	const bool& IsDelete() const { return m_bDead; }			// �׾����� üũ�Ͽ� ���� -> Manager���� Ȯ��
	
	void GetDamage(const int& nDamage)
	{
		m_nHp -= nDamage;
	}

	const bool IsDead() const { 
		if (m_nFrameType == TYPE_DEAD)
			return true; 
		else 
			return false;
	}
	const bool& InRange() const { return m_bInRange; }			// ���� ��Ÿ� �ȿ� �ִ���
	
	virtual int GetKey(const WPARAM& wParam) { return 0; }		// Ű���� �޴� �Լ�
	virtual void MouseMove(const LPARAM& lParam) {}				// ���콺 ���� �Լ���
	virtual void LButtonDown(const LPARAM& lParam) {}
	virtual int LButtonUp(const LPARAM& lParam) { return 0; }

	// enemy ���� ����
	virtual void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		if (vtPosition.GetX() - nWidth <= m_vtCoord.GetX() + m_nAttackRange)
			m_bInRange = true;
		else m_bInRange = false;
	}
	int ReturnTargeted() const { return m_nTargeted; }			// ���� �󸶳� Ÿ���� �Ǿ��ֳ�
private:

};