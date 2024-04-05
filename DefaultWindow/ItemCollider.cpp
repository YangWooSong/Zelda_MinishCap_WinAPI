#include "stdafx.h"
#include "ItemCollider.h"
#include "Boss1.h"
#include "LaserBall.h"
#include "Weapon.h"
#include "Player.h"
#include "EyeShield.h"

CItemCollider::CItemCollider()
{
    m_eId = OBJ_ITEMCOLLIDER;
    m_vSize = { 0.f, 0.f };
}

CItemCollider::~CItemCollider()
{
    Release();
}

void CItemCollider::Initialize()
{
    m_eRender = RENDER_GAMEOBJECT;
}

int CItemCollider::Update()
{
	if(m_pTarget)
		m_vPos = m_pTarget->Get_Pos();
    return 0;
}

void CItemCollider::Late_Update()
{
    m_vPos += m_vOffset;
    Set_Collider(m_vPos.x , m_vPos.y , m_vSize.x, m_vSize.y);
}

void CItemCollider::Render(HDC hDC)
{
   // RenderCollision(hDC);
}

void CItemCollider::OnCollisionEnter( CObj* _pOther)
{ 
	float   fX(0.f), fY(0.f);
	/*if (pMonster == nullptr)
		return;*/
	CObj* pObject = _pOther;

	//충돌체 종류 확인
	if (dynamic_cast<CMonster*>(_pOther) != nullptr)
	{
	//	pObject = dynamic_cast<CMonster*>(_pOther);
	}
		

	RECT intersect = {};

	if (::IntersectRect(&intersect, &pObject->Get_Collider(), &m_tCollider))
	{
		int w = intersect.right - intersect.left;
		int h = intersect.bottom - intersect.top;

		if (w > h)
		{
			if (intersect.top == m_tCollider.top)
			{
				//레이저 눈알일 경우a만
				if (pObject->Get_Id() == OBJ_EYES)
				{
					if (dynamic_cast<CLaserBall*>(pObject)->Get_ShieldActive() == true)
					{
						if (dynamic_cast<CPlayer*>(m_pTarget)->Get_ITEMID() == ITEM_POT)
							dynamic_cast<CLaserBall*>(pObject)->Set_ShieldActive(false);
						else
							return;
					}
					else pObject->Set_Hp(-1);
				}
				else 
				{
					pObject->Set_Hp(-1);
					pObject->Set_CurState(HIT);
				}
			}
			else
			{
				//레이저 눈알일 경우만
				if (pObject->Get_Id() == OBJ_EYES)
				{
					if (dynamic_cast<CLaserBall*>(pObject)->Get_ShieldActive() == true)
					{
						if (dynamic_cast<CPlayer*>(m_pTarget)->Get_ITEMID() == ITEM_POT)
							dynamic_cast<CLaserBall*>(pObject)->Set_ShieldActive(false);
						else
							return;
					}
					else pObject->Set_Hp(-1);
				}
				else
				{
					pObject->Set_Hp(-1);
					pObject->Set_CurState(HIT);
				}
			}
		}
		else
		{
			if (intersect.left == m_tCollider.left)
			{
				//레이저 눈알일 경우만
				if (pObject->Get_Id() == OBJ_EYES)
				{
					if (dynamic_cast<CLaserBall*>(pObject)->Get_ShieldActive() == true)
					{
						if (dynamic_cast<CPlayer*>(m_pTarget)->Get_ITEMID() == ITEM_POT)
							dynamic_cast<CLaserBall*>(pObject)->Set_ShieldActive(false);
						else
							return;
					}
					else pObject->Set_Hp(-1);
				}
				else
				{
					pObject->Set_Hp(-1);
					pObject->Set_CurState(HIT);
				}
			}
			else
			{
				//레이저 눈알일 경우만
				if (pObject->Get_Id() == OBJ_EYES)
				{
					if (dynamic_cast<CLaserBall*>(pObject)->Get_ShieldActive() == true)
					{
						if (dynamic_cast<CPlayer*>(m_pTarget)->Get_ITEMID() == ITEM_POT)
							dynamic_cast<CLaserBall*>(pObject)->Set_ShieldActive(false);
						else
							return;
					}
					else pObject->Set_Hp(-1);
				}
				else
				{
					pObject->Set_Hp(-1);
					pObject->Set_CurState(HIT);
				}
			}
		}

	}
}

void CItemCollider::Release()
{
}

