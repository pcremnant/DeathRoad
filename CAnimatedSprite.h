#pragma once
#include"define.h"

#define TYPE_WALK 0
#define TYPE_ATTACK 1
#define TYPE_DEAD 2

// 움직일 때 애니메이션이 발생하는 오브젝트를 위한 클래스
// 3가지 동작을 저장할 수 있고 GetImage를 통해 초기화
// Draw할때 hdc, 타입, 현재 프레임, 그릴 위치를 넘겨주면 자동으로 그려준다.
// MaxFrame을 통해 해당 동작의 최대 프레임을 리턴할 수 있다.

struct CAnimatedSprite {

	// 이미지 초기화	(걷기동작 주소, 공격동작 주소, 죽는동작 주소, 걷기동작 최대프레임, 공격동작 최대프레임, 죽는동작 최대프레임)
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
	// 이미지
	CImage m_imgWalk;
	CImage m_imgAttack;
	CImage m_imgDead;

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
