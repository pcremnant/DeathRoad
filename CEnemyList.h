#pragma once
#include"define.h"
#include"CEnemyInfant.h"
#include"SoundManager.h"

// ���� �Ŵ����� ����� ���� ���Ḯ��Ʈ�� ���
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

// ���� ���Ḯ��Ʈ
class CEnemyList {
	CSoundManager* m_pSoundManager;
public:

	CEnemyNode* m_pHead;
	CEnemyNode* m_pTail;

	CEnemyList(CSoundManager* sound) : m_pSoundManager(sound)
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

	// ����Ʈ�� ��� ���� - z���� �������� ū ���� �տ� �ִ�.
	// ������� �׷��ָ� �ڵ������� ��ġ��
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

	// ������Ʈ�� �ָ� �ش� ������Ʈ�� ������ �ִ� ��带 ��ȯ�Ѵ�.
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

	// ���� Ŭ������ �޾ƿ� ���� -> �Ŀ� �߰�
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
				int nTmp = p->m_pEnemy->Update();
				//if (nTmp == UNIT_ATTACK)
				//	m_pSoundManager->PlayEffect(EFFECT_INFANT_ATTACK_00);
				//else if (nTmp == UNIT_DEAD)
				//	m_pSoundManager->PlayEffect(EFFECT_INFANT_DEAD_00);
				p = p->m_pNext;
			}
		}
	}

	void SetTarget(const CVector3D& vtPosition, const int& nWidth)
	{
		CEnemyNode* p = m_pHead->m_pNext;
		while (p != m_pTail) {
			p->m_pEnemy->SetTarget(vtPosition, nWidth);
			p = p->m_pNext;
		}
	}

	int GetNumber() const
	{
		CEnemyNode* p = m_pHead->m_pNext;
		int nTmp = 0;
		while (p != m_pTail) {
			nTmp++;
			p = p->m_pNext;
		}
		return nTmp;
	}
};