#pragma once
#include"CItem.h"

#define OBJECT_TYPE_CASTLE 10000
#define OBJECT_TYPE_ARROW 10001
class CCastle : public CItem {

public:
	void Init() override;
	void Move() override;
	void DrawItem(HDC hdc) override;
};