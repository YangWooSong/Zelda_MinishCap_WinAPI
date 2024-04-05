#include "stdafx.h"
#include "ShieldCollider.h"
#include "SoundMgr.h"

CShieldCollider::CShieldCollider() : m_bActive(false), m_bSound(true)
{
}

CShieldCollider::~CShieldCollider()
{
	Release();
}

void CShieldCollider::Initialize()
{
	m_eId = OBJ_MONSTER;
	m_eRender = RENDER_GAMEOBJECT;
	m_vSize = { 0.f, 0.f };
	m_vOffset = { 0.f,0.f };
}

int CShieldCollider::Update()
{
	if (m_pTarget)
		m_vPos = m_pTarget->Get_Pos();

	return 0;
}

void CShieldCollider::Late_Update()
{
	m_vPos += m_vOffset;
	if(m_bActive == false)
	{
		Set_Collider(m_vPos.x, m_vPos.y, 0, 0);
	//	m_bSound = true;
	}
	else
	{
		Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
	}
}

void CShieldCollider::Render(HDC hDC)
{
	if(m_bActive)
	{
		//RenderCollision(hDC);
	}
}

void CShieldCollider::Release()
{
}
