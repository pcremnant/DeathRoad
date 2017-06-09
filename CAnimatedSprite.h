#pragma once
#include"define.h"

#define TYPE_WALK 0
#define TYPE_ATTACK 1
#define TYPE_DEAD 2

// ������ �� �ִϸ��̼��� �߻��ϴ� ������Ʈ�� ���� Ŭ����
// 3���� ������ ������ �� �ְ� GetImage�� ���� �ʱ�ȭ
// Draw�Ҷ� hdc, Ÿ��, ���� ������, �׸� ��ġ�� �Ѱ��ָ� �ڵ����� �׷��ش�.
// MaxFrame�� ���� �ش� ������ �ִ� �������� ������ �� �ִ�.

struct CAnimatedSprite {

	// �̹��� �ʱ�ȭ	(�ȱ⵿�� �ּ�, ���ݵ��� �ּ�, �״µ��� �ּ�, �ȱ⵿�� �ִ�������, ���ݵ��� �ִ�������, �״µ��� �ִ�������)
	void GetImage(LPCTSTR walk, LPCTSTR attack, LPCTSTR dead, const int& walkFrame, const int& attackFrame, const int& deadFrame)
	{
		m_imgWalk.Load(walk);
		m_imgAttack.Load(attack);
		m_imgDead.Load(dead);
		m_nWalkFrame = walkFrame;
		m_nAttackFrame = attackFrame;
		m_nDeadFrame = deadFrame;

		m_nWalkWidth = m_imgWalk.GetWidth() / m_nWalkFrame;
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
	// �̹���
	CImage m_imgWalk;
	CImage m_imgAttack;
	CImage m_imgDead;

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
