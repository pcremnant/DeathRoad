#pragma once
#include"define.h"
#include"CCrossbowArrow.h"

class CEnemyArrowNode {
public:
	CEnemyArrow* m_pData;
	CEnemyArrowNode* m_pNext;
	CEnemyArrowNode* m_pPrev;

	CEnemyArrowNode(CEnemyArrow* newArrow) : m_pData(newArrow)
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	CEnemyArrowNode()
	{
		m_pData = nullptr;
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CEnemyArrowNode()
	{
		if (m_pData)
			delete m_pData;
	}
};

class CEnemyArrowList {

public:
	CEnemyArrowNode* m_pHead;
	CEnemyArrowNode* m_pTail;
	CEnemyArrowList()
	{
		m_pHead = new CEnemyArrowNode();
		m_pTail = new CEnemyArrowNode();
		m_pHead->m_pNext = m_pTail;
		m_pTail->m_pPrev = m_pHead;
	}
	~CEnemyArrowList()
	{
		CEnemyArrowNode* p = m_pHead;
		CEnemyArrowNode* next = p->m_pNext;
		while (next != m_pTail) {
			p->m_pNext = next->m_pNext;
			delete next;
			next->m_pNext = p->m_pNext;
		}
		delete m_pHead;
		delete m_pTail;
	}

	void Insert(CEnemyArrow* newArrow)
	{
		CEnemyArrowNode* newData = new CEnemyArrowNode(newArrow);
		
		if (m_pHead->m_pNext == m_pTail) {
			newData->m_pNext = m_pTail;
			newData->m_pPrev = m_pHead;
			m_pHead->m_pNext = newData;
			m_pTail->m_pPrev = newData;
			return;
		}

		CEnemyArrowNode* p = m_pHead->m_pNext;
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

	void Delete(CEnemyArrowNode* delNode)
	{
		delNode->m_pNext->m_pPrev = delNode->m_pPrev;
		delNode->m_pPrev->m_pNext = delNode->m_pNext;
		delete delNode;
	}

	void Pop()
	{
		CEnemyArrowNode* p = m_pHead;
		CEnemyArrowNode* next = p->m_pNext;
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
		CEnemyArrowNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			p->m_pData->DrawItem(hdc);
			p = p->m_pNext;
		}
	}

	void Update()
	{
		CEnemyArrowNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			if (p->m_pData->IsDelete()) {
				CEnemyArrowNode* tmp = p->m_pNext;
				Delete(p);
				p = tmp;
			}
			else {
				p->m_pData->Move();
				p = p->m_pNext;
			}
		}
	}

	/*void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		CEnemyArrowNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			p->m_pData->SetTarget(vtPosition, nWidth);
			p = p->m_pNext;
		}
	}*/
};