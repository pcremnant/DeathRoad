#include"CObject.h"

void CObject::GetDamage(const int & nDamage)
{
	m_nHp -= nDamage;
}

void CObject::GetTarget()
{
	m_nTargeted++;
}

const bool CObject::IsDead() const {
	if (m_nFrameType == TYPE_DEAD)
		return true;
	else
		return false;
}

// enemy 전용 세팅

void CObject::SetTarget(const CVector3D & vtPosition, const int & nWidth)
{
	if (vtPosition.GetX() - nWidth <= m_vtCoord.GetX() + m_nAttackRange)
		m_bInRange = true;
	else m_bInRange = false;
}
