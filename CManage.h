#pragma once
#include"define.h"


#define ICON_NUMBER 2
// 아이콘 고유번호
#define ICON_EXIT 100
#define ICON_BATTLESTART 101


class CManage {
	// 매니지 모드 이미지
	CImage m_imgBG;							// 배경 이미지
	CImage m_imgIcon[ICON_NUMBER];			// 아이콘 이미지 - 위의 디파인값으로 읽는다.
	RECT m_rcIcon[ICON_NUMBER];				// 아이콘 위치 - 역시 위의 디파인값으로 읽는다.


public:
	void Init()
	{

	}

	CManage() {};
};