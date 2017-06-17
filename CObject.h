#pragma once
#include"define.h"
#include"CVector3D.h"
#include"CAnimatedSprite.h"
#include"SoundManager.h"

#define UNIT_NONE 0
#define UNIT_ATTACK -1
#define UNIT_DEAD -2

// 움직일 때 애니메이션이 발생하는 오브젝트 클래스
class CObject {
protected:
	// 이미지 정보
	CAnimatedSprite m_sprImg;
	int m_nFrameType{ 0 };
	int m_nFrame{ 0 };

	// 오브젝트의 위치정보
	CVector3D m_vtCoord{ 0,0,0 };			// 좌표
	int m_nWidth{ 0 };						// x 크기 -> 중심 기준으로 좌 우 끝까지의 거리
	int m_nHeight{ 0 };						// y 크기 -> 중심 기준으로 상 하 끝까지의 거리
											// 실질적인 바운딩박스(충돌 박스)						

	RECT m_rcPosition{ 0,0,0,0 };			// 실제 이미지가 나오는 사각형

	bool m_bInRange{ false };				// 공격 사거리 안에 있는가
	bool m_bAttackCharge{ false };			// 공격을 준비하고 있는가 (활 시위를 당기고 있는 때)
	bool m_bReroad{ false };				// 재장전중인가
	int m_nAttackRange{ 0 };				// 공격 사거리
	int m_nAttack{ 0 };						// 공격력
	int m_nAttackFrame{ 0 };				// 효과음을 낼 프레임
	int m_nMaxHp{ 0 };						// 최대체력
	int m_nHp{ 0 };							// 현재체력
	bool m_bDead{ false };					// 오브젝트가 죽었는가
	int m_nTargeted{ 0 };					// 현재 타게팅 된 수

	CSoundManager* m_pSoundManager{ nullptr };
public:
	CObject(CSoundManager* sound) : m_pSoundManager(sound) {}
	virtual void Init() {};										// 초기화 해주는 함수
	virtual void DrawObject(HDC hdc) {};						// 드로우 함수
	virtual int Update() = 0;
	virtual void Move() {};										// Update시 움직이는 함수
	virtual int Attack() = 0;									// Update시 공격하는 함수
	virtual int Dead() = 0;										// Update시 죽는 함수
	virtual void GetUpgrade() {};								// 배틀페이즈 시작시 (혹은 오브젝트 생성시) 업그레이드 정보를 정해준다.
	virtual void SetPosition() {};								// m_vtCoord에 따라 바운딩 박스(이미지 위치 및 크기)를 정해주는 함수
	virtual void SetFrameType(const int& nType) {};				// 특정 상황에서 동작을 바꿔준다.(걷다가 사거리 안으로 들어오면 공격 모션으로 바꿔줌)
	const float ReturnZ() const { return m_vtCoord.GetZ(); }	// 충돌판정을 위해 z값을 리턴
	CVector3D ReturnCoord()const { return m_vtCoord; }			// 좌표 리턴
	RECT ReturnPosition() const { return m_rcPosition; }		// 사각형 리턴
	const bool& IsDelete() const { return m_bDead; }			// 죽었는지 체크하여 보냄 -> Manager에서 확인
	
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
	const bool& InRange() const { return m_bInRange; }			// 공격 사거리 안에 있는지
	
	virtual int GetKey(const WPARAM& wParam) { return 0; }		// 키보드 받는 함수
	virtual void MouseMove(const LPARAM& lParam) {}				// 마우스 관련 함수들
	virtual void LButtonDown(const LPARAM& lParam) {}
	virtual int LButtonUp(const LPARAM& lParam) { return 0; }

	// enemy 전용 세팅
	virtual void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		if (vtPosition.GetX() - nWidth <= m_vtCoord.GetX() + m_nAttackRange)
			m_bInRange = true;
		else m_bInRange = false;
	}
	int ReturnTargeted() const { return m_nTargeted; }			// 현재 얼마나 타게팅 되어있나
private:

};