#pragma once
#include<Windows.h>

class CFunc {
public:
	static LONG FloorFromY(const float& fZ)
	{
		int nY = 250 + static_cast<float>((5 - (fZ - 1) * 10) * 40);
		return nY;
	}
};