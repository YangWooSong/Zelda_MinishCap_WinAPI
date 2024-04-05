#include "stdafx.h"
#include "Door.h"
#include "Player.h"
CDoor::CDoor() : m_eId(ITEM_END), m_pSceneChagne(nullptr)
{
}

CDoor::~CDoor()
{
}

void CDoor::Initialize()
{
    m_eRender = RENDER_GAMEOBJECT;
}

int CDoor::Update()
{
    return 0;
}

void CDoor::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, 40.f, 40.f);
}

void CDoor::OnCollisionEnter(CObj* _pOther)
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
                *m_pSceneChagne = true;
            }
            else
            {
                *m_pSceneChagne = true;
            }
        }
        else
        {
            if (intersect.left == m_tCollider.left)
            {

                *m_pSceneChagne = true;

            }
            else
            {
                *m_pSceneChagne = true;
            }
        }
    }
}

void CDoor::Render(HDC hDC)
{
   // RenderCollision(hDC);
}




void CDoor::Release()
{
}
