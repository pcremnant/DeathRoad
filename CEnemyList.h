#pragma once
#include"define.h"
#include"CEnemyInfant.h"

// 적군 매니저를 만들기 위한 열결리스트의 노드
class CEnemyNode {
public:
	CObject* m_pEnemy;
	CEnemyNode* m_pNext;
	CEnemyNode* m_pPrev;
	
	CEnemyNode()
	{
		m_pEnemy = nullptr;
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	CEnemyNode(CObject* newEnemy) : m_pEnemy(newEnemy)
	{
		m_pEnemy->Init();
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CEnemyNode()
	{
		if (m_pEnemy)
			delete m_pEnemy;
	}
};

// 적군 연결리스트
class CEnemyList {
public:
	CEnemyNode* m_pHead;
	CEnemyNode* m_pTail;

	CEnemyList()
	{
		m_pHead = new CEnemyNode;
		m_pTail = new CEnemyNode;
		m_pHead->m_pNext = m_pTail;
		m_pTail->m_pPrev = m_pHead;
	}
	~CEnemyList()
	{
		CEnemyNode* p = m_pHead;
		CEnemyNode* next = p->m_pNext;
		while (next!= m_pTail) {
			next->m_pNext = p->m_pNext;
			delete next;
			next = p->m_pNext;
		}
		delete m_pHead;
		delete m_pTail;
	}

	void Pop()
	{
		CEnemyNode* p = m_pHead;
		CEnemyNode* next = p->m_pNext;
		while (next != m_pTail) {
			p->m_pNext = next->m_pNext;
			delete next;
			next = p->m_pNext;
		}
		m_pHead->m_pNext = m_pTail;
		m_pTail->m_pPrev = m_pHead;
	}

	// 리스트에 노드 삽입 - z축을 기준으로 큰 값이 앞에 있다.
	// 순서대로 그려주면 자동적으로 배치됨
	void Insert(CObject* newEnemy)
	{
		CEnemyNode* newNode = new CEnemyNode(newEnemy);
		CEnemyNode* p = m_pHead->m_pNext;
		
		if (m_pHead->m_pNext == m_pTail) {
			newNode->m_pNext = m_pTail;
			newNode->m_pPrev = m_pHead;
			m_pHead->m_pNext = newNode;
			m_pTail->m_pPrev = newNode;
			return;
		}

		while (p != m_pTail) {
			if (p->m_pEnemy->ReturnZ() < newNode->m_pEnemy->ReturnZ()) {
				newNode->m_pNext = p;
				newNode->m_pPrev = p->m_pPrev;
				p->m_pPrev->m_pNext = newNode;
				p->m_pPrev = newNode;
				return;
			}
			else
				p = p->m_pNext;
		}

		newNode->m_pNext = m_pTail;
		newNode->m_pPrev = m_pTail->m_pPrev;
		m_pTail->m_pPrev->m_pNext = newNode;
		m_pTail->m_pPrev = newNode;
	}

	void Delete(CEnemyNode* delEnemy)
	{
		delEnemy->m_pPrev->m_pNext = delEnemy->m_pNext;
		delEnemy->m_pNext->m_pPrev = delEnemy->m_pPrev;
		delete delEnemy;
	}

	// 오브젝트를 주면 해당 오브젝트를 가지고 있는 노드를 반환한다.
	CEnemyNode* Search(CObject* searchObj)
	{
		CEnemyNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			if (p->m_pEnemy == searchObj)
				return p;
			else
				p = p->m_pNext;
		}
		return nullptr;
	}

	void DrawObj(HDC hdc)
	{
		CEnemyNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			p->m_pEnemy->DrawObject(hdc);
			p = p->m_pNext;
		}
	}

	void Update()
	{
		CEnemyNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			if (p->m_pEnemy->IsDelete()) {
				CEnemyNode* tmp = p->m_pNext;
				Delete(p);
				p = tmp;
			}
			else {
				p->m_pEnemy->Move();
				p = p->m_pNext;
			}
		}
	}
};