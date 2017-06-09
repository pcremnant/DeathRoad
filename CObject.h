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

// 움직일 때 애니메이션이 발생하는 오브젝트를 위한 클래스
// 3가지 동작을 저장할 수 있고 GetImage를 통해 초기화
// Draw할때 hdc, 타입, 현재 프레임, 그릴 위치를 넘겨주면 자동으로 그려준다.
// MaxFrame을 통해 해당 동작의 최대 프레임을 리턴할 수 있다.

struct Sprite {

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

// 움직일 때 애니메이션이 발생하는 오브젝트 클래스
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

	bool m_bInRange;					// 공격 사거리 안에 있는가
	bool m_bAttackCharge;				// 공격을 준비하고 있는가 (활 시위를 당기고 있는 때)
	int m_nAttackRange;					// 공격 사거리

	bool m_bDead;						// 오브젝트가 죽었는가
public:

	virtual void Init() {};										// 초기화 해주는 함수
	virtual void DrawObject(HDC hdc) {};						// 드로우 함수
	virtual void Move() {};										// Update시 움직이는 함수
	virtual void GetUpgrade() {};								// 배틀페이즈 시작시 (혹은 오브젝트 생성시) 업그레이드 정보를 정해준다.
	virtual void SetPosition() {};								// m_vtCoord에 따라 바운딩 박스(이미지 위치 및 크기)를 정해주는 함수
	virtual void SetFrameType(const int& nType) {};				// 특정 상황에서 동작을 바꿔준다.(걷다가 사거리 안으로 들어오면 공격 모션으로 바꿔줌)
	const float ReturnZ() const { return m_vtCoord.GetZ(); }	// 충돌판정을 위해 z값을 리턴
	const bool& IsDelete() const { return m_bDead; }			// 죽었는지 체크하여 보냄
	void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		if (vtPosition.GetX() - nWidth <= m_vtCoord.GetX() + m_nAttackRange)
			m_bInRange = true;
		else m_bInRange = false;
	}
private:

};