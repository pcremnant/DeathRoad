#pragma once
#include<Windows.h>

class CFunc {
public:
	static LONG FloorFromY(const float& fZ, const bool& bPlayer = false)
	{
		if (bPlayer)
			return 300 + 50 * 40;
		else {
			int nY = 300 + static_cast<float>((5 - (fZ - 1) * 10) * 40);
			return nY;
		}
	}
};