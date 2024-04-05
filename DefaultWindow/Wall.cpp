#include "stdafx.h"
#include "Wall.h"
#include "Player.h"
#include "Camera.h"

CWall::CWall()
{
}

CWall::~CWall()
{
    m_vSize.x = 10.f;
    m_vSize.y = 10.f;
}

void CWall::Initialize()
{
    Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
    m_eRender = RENDER_GAMEOBJECT;

    m_eId = OBJ_WALL;
}

int CWall::Update()
{
    return 0;
}

void CWall::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void CWall::Render(HDC hDC)
{
   // RenderCollision(hDC);
}

void CWall::OnCollisionEnter(CObj* _pOther)
{
    float   fX(0.f), fY(0.f);
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

    if (pPlayer == nullptr)
        return;
    RECT intersect = {};

    if (::IntersectRect(&intersect, &pPlayer->Get_Collider(),&m_tCollider))
    {
        int w = intersect.right - intersect.left;
        int h = intersect.bottom - intersect.top;

        if (w > h)
        {
            if (intersect.top == m_tCollider.top)
            {
               // pPlayer->Set_PosY(-h + 1);
                pPlayer->Set_PosY(pPlayer->Get_Pos().y - h -4);
            }
            else
            {
              // pPlayer->Set_PosY(h + 1);
                pPlayer->Set_PosY(pPlayer->Get_Pos().y+ h + 4);
            }
        }
        else
        {
            if (intersect.left == m_tCollider.left)
            {

                pPlayer->Set_PosX(pPlayer->Get_Pos().x - w - 4);
               
            }
            else
            {
                pPlayer->Set_PosX(w + pPlayer->Get_Pos().x + 4 );
            }
        }

    }
}

void CWall::OnCollisionStay(CObj* _pOther)
{
    float   fX(0.f), fY(0.f);
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

    if (pPlayer == nullptr)
        return;

    RECT intersect = {};

    if (::IntersectRect(&intersect, &pPlayer->Get_Collider(), &m_tCollider))
    {
        int w = intersect.right - intersect.left;
        int h = intersect.bottom - intersect.top;

        if (w > h)
        {
            if (intersect.top == m_tCollider.top)
            {
                pPlayer->Set_PosY(-h + 1.f);

            }
            else
            {
                pPlayer->Set_PosY(h + 1.f);
                return;
            }
        }
        else
        {
            if (intersect.left == m_tCollider.left)
            {
                pPlayer->Set_PosX(-w);
            }
            else
            {
                pPlayer->Set_PosX(w);

            }
        }
    }

}

void CWall::OnCollisionExit(CObj* _pOther)
{

}

void CWall::Release()
{
}
