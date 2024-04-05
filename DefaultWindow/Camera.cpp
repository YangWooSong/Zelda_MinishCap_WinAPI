#include "stdafx.h"
#include "Camera.h"
#include "Obj.h"
#include "KeyMgr.h"

CCamera* CCamera::m_pInstance = nullptr;

CCamera::CCamera() : m_pTarget(nullptr), m_fZoom(1.f)
{
	ZeroMemory(&m_vMaxPos, sizeof(VEC2));
	ZeroMemory(&m_vMinPos, sizeof(VEC2));
}

CCamera::~CCamera()
{
}



VEC2 CCamera::GetRenderPos(VEC2 _vObjPos)
{
	return _vObjPos - m_tDiff;
}

VEC2 CCamera::GetRenderPos(float _x, float _y)
{
	return VEC2(_x - m_tDiff.x, _y - m_tDiff.y);
}

VEC2 CCamera::GetWindowPos(VEC2 _vObjPos)
{
	return _vObjPos + m_tDiff;
}

VEC2 CCamera::GetWindowPos(float _x, float _y)
{
	return VEC2(m_tDiff.x + _x, m_tDiff.y + _y);
}

void CCamera::Initialize()
{
}

void CCamera::Update()
{
	if (m_pTarget)
	{
		if (m_pTarget->Get_Dead() == true)
			m_pTarget = nullptr;
		else
		{
			if ((m_pTarget->m_vPos.x <= m_vMaxPos.x && m_pTarget->m_vPos.x >= m_vMinPos.x))
			{

				m_tLookAtPos.x = m_pTarget->m_vPos.x;
			}
			else
			{
			}

			if ((m_pTarget->m_vPos.y <= m_vMaxPos.y && m_pTarget->m_vPos.y >= m_vMinPos.y))
			{
				m_tLookAtPos.y = m_pTarget->m_vPos.y;
			}

		}
	}

	CalculateDiff();

	/*if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		m_tLookAtPos.y -= 10.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		m_tLookAtPos.x-= 10.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		m_tLookAtPos.y += 10.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		m_tLookAtPos.x += 10.f;
	}*/
}

void CCamera::Render(HDC hDC)
{
}

void CCamera::CalculateDiff()
{
	VEC2 vCenter(WINCX * 0.5f, WINCY * 0.5f);

	m_tDiff = (m_tLookAtPos - vCenter);
}
