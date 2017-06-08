#pragma once
#include"define.h"
#include"CVector3D.h"

// ������ �� �ִϸ��̼��� ���� ������Ʈ
class CItem {
protected:
	CImage m_imgBitmap;

	// ��ü�� ��ġ��
	CVector3D m_vtCoord{ 0,0,0 };
	int m_nWidth{ 0 };
	int m_nHeight{ 0 };
	RECT m_rcPosition{ 0,0,0,0 };

	// ��ü�� ������ �ִ� ��
	int m_nValue{ 0 };											//���̸� ü��, ȭ���̸� ���ݷ��� �ȴ�.
	int m_nObjectType{ 0 };
public:
	virtual void Init() = 0;
	virtual void Move() = 0;
	virtual void DrawItem(HDC hdc) = 0;

	// �浹üũ�� ���� �Լ�
	const RECT& GetPositionRc() const
	{
		return m_rcPosition;
	}
	const CVector3D& GetPositionVt() const
	{
		return m_vtCoord;
	}
	const int& GetWidth() const
	{
		return m_nWidth;
	}
};