#pragma once
#include"define.h"
#include"CPlayerArrow.h"
#include"CObject.h"
#include"CArrow.h"

class CPlayerArrowNode {
public:
	CPlayerArrow* m_pData;
	CPlayerArrowNode* m_pNext;
	CPlayerArrowNode* m_pPrev;
	CPlayerArrowNode(CPlayerArrow* newArrow) : m_pData(newArrow)
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	CPlayerArrowNode()
	{
		m_pData = nullptr;
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CPlayerArrowNode()
	{
		if (m_pData)
			delete m_pData;
	}
};

class CPlayerArrowList {

public:
	CPlayerArrowNode* m_pHead;
	CPlayerArrowNode* m_pTail;
	CPlayerArrowList()
	{
		m_pHead = new CPlayerArrowNode();
		m_pTail = new CPlayerArrowNode();
		m_pHead->m_pNext = m_pTail;
		m_pTail->m_pPrev = m_pHead;
	}
	~CPlayerArrowList()
	{
		CPlayerArrowNode* p = m_pHead;
		CPlayerArrowNode* next = p->m_pNext;
		while (next != m_pTail) {
			p->m_pNext = next->m_pNext;
			delete next;
			next = p->m_pNext;
		}
		delete m_pHead;
		delete m_pTail;
	}

	void Insert(CPlayerArrow* newArrow)
	{
		CPlayerArrowNode* newData = new CPlayerArrowNode(newArrow);

		if (m_pHead->m_pNext == m_pTail) {
			newData->m_pNext = m_pTail;
			newData->m_pPrev = m_pHead;
			m_pHead->m_pNext = newData;
			m_pTail->m_pPrev = newData;
			return;
		}

		CPlayerArrowNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			if (newData->m_pData->GetPositionVt().GetZ() > p->m_pData->GetPositionVt().GetZ()) {
				newData->m_pNext = p;
				newData->m_pPrev = p->m_pPrev;
				p->m_pPrev->m_pNext = newData;
				p->m_pPrev = newData;
				return;
			}
			else
				p = p->m_pNext;
		}

		if (p == m_pTail) {
			newData->m_pNext = m_pTail;
			newData->m_pPrev = m_pTail->m_pPrev;
			m_pTail->m_pPrev->m_pNext = newData;
			m_pTail->m_pPrev = newData;
			return;
		}
	}

	void Delete(CPlayerArrowNode* delNode)
	{
		delNode->m_pNext->m_pPrev = delNode->m_pPrev;
		delNode->m_pPrev->m_pNext = delNode->m_pNext;
		delete delNode;
	}

	void Pop()
	{
		CPlayerArrowNode* p = m_pHead;
		CPlayerArrowNode* next = p->m_pNext;
		while (next != m_pTail) {
			p->m_pNext = next->m_pNext;
			delete next;
			next = p->m_pNext;
		}
		m_pHead->m_pNext = m_pTail;
		m_pTail->m_pPrev = m_pHead;
	}

	void DrawObj(HDC hdc)
	{
		CPlayerArrowNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			p->m_pData->DrawItem(hdc);
			p = p->m_pNext;
		}
	}

	void Update()
	{
		CPlayerArrowNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			if (p->m_pData->IsDelete()) {
				CPlayerArrowNode* tmp = p->m_pNext;
				Delete(p);
				p = tmp;
			}
			else {
				p->m_pData->Move();
				p = p->m_pNext;
			}
		}
	}

	void ColisionCheck(CObject* enemy)
	{
		if (enemy == nullptr)
			return;
		CPlayerArrowNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			if (p->m_pData->GetPositionVt().GetZ() == enemy->ReturnZ()) {
				if (p->m_pData->ColisionCheck(enemy->ReturnPosition())) {
					enemy->GetDamage(p->m_pData->ReturnValue());
					p->m_pData->SetTarget(enemy);
				}
			}
			p = p->m_pNext;
		}
	}
};