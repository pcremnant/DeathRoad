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

	}

};