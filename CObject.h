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

// 움직일 때 애니메이션이 발생하는 오브젝트 클래스
class CObject {
protected:
	// 이미지 정보
	CAnimatedSprite m_sprImg;
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
	virtual int Update() = 0;
	virtual void Move() {};										// Update시 움직이는 함수
	virtual int Attack() = 0;									// Update시 공격하는 함수
	virtual void Dead() {}										// Update시 죽는 함수
	virtual void GetUpgrade() {};								// 배틀페이즈 시작시 (혹은 오브젝트 생성시) 업그레이드 정보를 정해준다.
	virtual void SetPosition() {};								// m_vtCoord에 따라 바운딩 박스(이미지 위치 및 크기)를 정해주는 함수
	virtual void SetFrameType(const int& nType) {};				// 특정 상황에서 동작을 바꿔준다.(걷다가 사거리 안으로 들어오면 공격 모션으로 바꿔줌)
	const float ReturnZ() const { return m_vtCoord.GetZ(); }	// 충돌판정을 위해 z값을 리턴
	const bool& IsDelete() const { return m_bDead; }			// 죽었는지 체크하여 보냄
	const bool& InRange() const { return m_bInRange; }			// 공격 사거리 안에 있는지
	void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		if (vtPosition.GetX() - nWidth <= m_vtCoord.GetX() + m_nAttackRange)
			m_bInRange = true;
		else m_bInRange = false;
	}
private:

};