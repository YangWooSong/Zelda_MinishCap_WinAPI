#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

CMonster::CMonster() : m_bHit(false)
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
}

int CMonster::Update()
{
    return 0;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC hDC)
{
}


void CMonster::OnCollisionEnter(CObj* _pOther)
{
	float   fX(0.f), fY(0.f);

	RECT intersect = {};

	if (::IntersectRect(&intersect, &_pOther->Get_Collider(), &m_tCollider))
	{
		int w = intersect.right - intersect.left;
		int h = intersect.bottom - intersect.top;

		if (w > h)
		{
			if (intersect.top == m_tCollider.top)
			{
				if(_pOther->Get_Id() == OBJ_PLAYER)
				{
					dynamic_cast<CPlayer*>(_pOther)->Set_PosY(_pOther->Get_Pos().y - h - 4);
					dynamic_cast<CPlayer*>(_pOther)->Set_CurHp(-1);
					dynamic_cast<CPlayer*>(_pOther)->Set_Hit(true);

					if (this->m_eId == OBJ_BULLET)
					{
						m_iHp = 0;
					}
				}

				if (_pOther->Get_Id() == OBJ_WALL)
				{
					if (this->m_eId == OBJ_BULLET)
					{
						m_iHp = 0;
					}
				}
			}
			else
			{
				if (_pOther->Get_Id() == OBJ_PLAYER)
				{
					dynamic_cast<CPlayer*>(_pOther)->Set_PosY(_pOther->Get_Pos().y + h + 4);
					dynamic_cast<CPlayer*>(_pOther)->Set_CurHp(-1);
					dynamic_cast<CPlayer*>(_pOther)->Set_Hit(true);

					if (this->m_eId == OBJ_BULLET)
					{
						m_iHp = 0;
					}
				}
				if (_pOther->Get_Id() == OBJ_WALL)
				{
					if (this->m_eId == OBJ_BULLET)
					{
						m_iHp = 0;
					}
				}
			}
		}
		else
		{
			if (intersect.left == m_tCollider.left)
			{
				if (_pOther->Get_Id() == OBJ_PLAYER)
				{
					dynamic_cast<CPlayer*>(_pOther)->Set_PosX(_pOther->Get_Pos().x - w - 4);
					dynamic_cast<CPlayer*>(_pOther)->Set_CurHp(-1);
					dynamic_cast<CPlayer*>(_pOther)->Set_Hit(true);

					if (this->m_eId == OBJ_BULLET)
					{
						m_iHp = 0;
					}
				}
				if (_pOther->Get_Id() == OBJ_WALL)
				{
					if (this->m_eId == OBJ_BULLET)
					{
						m_iHp = 0;
					}
				}
			}
			else
			{
				if (_pOther->Get_Id() == OBJ_PLAYER)
				{
					dynamic_cast<CPlayer*>(_pOther)->Set_PosX(w + _pOther->Get_Pos().x + 4);
					dynamic_cast<CPlayer*>(_pOther)->Set_CurHp(-1);
					dynamic_cast<CPlayer*>(_pOther)->Set_Hit(true);

					if (this->m_eId == OBJ_BULLET)
					{
						m_iHp = 0;
					}
				}
				if (_pOther->Get_Id() == OBJ_WALL)
				{
					if (this->m_eId == OBJ_BULLET)
					{
						m_iHp = 0;
					}
				}
			}
		}

	}
}

void CMonster::Release()
{
}
