#pragma once
#include"define.h"


#define ICON_NUMBER 2
// ������ ������ȣ
#define ICON_EXIT 100
#define ICON_BATTLESTART 101


class CManage {
	// �Ŵ��� ��� �̹���
	CImage m_imgBG;							// ��� �̹���
	CImage m_imgIcon[ICON_NUMBER];			// ������ �̹��� - ���� �����ΰ����� �д´�.
	RECT m_rcIcon[ICON_NUMBER];				// ������ ��ġ - ���� ���� �����ΰ����� �д´�.


public:
	void Init()
	{

	}

	CManage() {};
};