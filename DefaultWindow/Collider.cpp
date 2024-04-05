#include "stdafx.h"
#include "Collider.h"
#include "Obj.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
{
}

CCollider::~CCollider()
{
}

void CCollider::Late_Update()
{
	
	VEC2 vObjectPos = m_pOwner->Get_Pos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::Render(HDC _hDC)
{
	Rectangle(_hDC, m_vFinalPos.x - m_vScale.x * 0.5f,
		int(m_vFinalPos.y - m_vScale.y * 0.5f),
		int(m_vFinalPos.x + m_vScale.x * 0.5f),
		int(m_vFinalPos.y + m_vScale.y * 0.5f));
}
