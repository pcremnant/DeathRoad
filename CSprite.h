#pragma once
#include"define.h"

struct CSprite {
	~CSprite()
	{
		m_imgSprite.Destroy();
		if (m_bExist)
			m_imgPointed.Destroy();
	}
	void GetImage(LPCTSTR path, const RECT& rcPosition, LPCTSTR pointedPath = nullptr)
	{
		m_bPointed = false;
		m_imgSprite.Load(path);
		
		if (pointedPath != nullptr) {
			m_imgPointed.Load(pointedPath);
			m_bExist = true;
		}
		else
			m_bExist = false;
		m_nWidth = m_imgSprite.GetWidth();
		m_nHeight = m_imgSprite.GetHeight();
		m_rcPosition = rcPosition;

		if (m_imgSprite.GetBPP() == 32)
		{
			unsigned char * pCol = 0;
			long w = m_imgSprite.GetWidth();
			long h = m_imgSprite.GetHeight();
			for (long y = 0; y < h; y++)
			{
				for (long x = 0; x < w; x++)
				{
					pCol = (unsigned char *)m_imgSprite.GetPixelAddress(x, y);
					unsigned char alpha = pCol[3];
					if (alpha != 255)
					{
						pCol[0] = ((pCol[0] * alpha) + 128) >> 8;
						pCol[1] = ((pCol[1] * alpha) + 128) >> 8;
						pCol[2] = ((pCol[2] * alpha) + 128) >> 8;
					}
				}
			}
			m_imgSprite.SetHasAlphaChannel(true);
		}
	}

	void InMouse(const LPARAM& lParam)
	{
		if (m_bExist) {
			int mx = LOWORD(lParam);
			int my = HIWORD(lParam);
			if (PtInRect(&m_rcPosition, POINT{ mx,my }))
				m_bPointed = true;
			else
				m_bPointed = false;
		}
	}

	void DrawSprite(HDC hdc, bool bTrans = false) const
	{
		RECT rcTmp = { 0,0,m_nWidth,m_nHeight };
		if (!m_bPointed) {
			if (bTrans)
				m_imgSprite.TransparentBlt(hdc, m_rcPosition, rcTmp, RGB(255, 255, 255));
			else
				m_imgSprite.Draw(hdc, m_rcPosition, rcTmp);
		}
		else {
			if (bTrans)
				m_imgPointed.TransparentBlt(hdc, m_rcPosition, rcTmp, RGB(255, 255, 255));
			else
				m_imgPointed.Draw(hdc, m_rcPosition, rcTmp);
		}
	}

	const bool& GetPointed() const
	{
		return m_bPointed;
	}

	const RECT& GetPosition() const
	{
		return m_rcPosition;
	}
private:
	CImage m_imgSprite;
	UINT m_nWidth;
	UINT m_nHeight;
	RECT m_rcPosition;

	// 마우스 등으로 선택되었을 때
	CImage m_imgPointed;					// 원래의 스프라이트와 크기, 위치가 같아야 한다.		
	bool m_bPointed;						// 선택 되었는지 확인
	bool m_bExist;							// 선택시 변형 스프라이트가 있는지 확인
};