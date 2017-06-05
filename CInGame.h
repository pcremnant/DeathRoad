#pragma once
#include"define.h"

class CInGame {

public:
	

	// 키보드 명령 받는 함수
	void GetKey(const WPARAM& wParam)
	{
		switch (wParam) {

		default:
			break;
		}
	}

	// 게임 안에서 그려주는 함수
	void DrawInGame(HDC hdc)
	{

	}
};