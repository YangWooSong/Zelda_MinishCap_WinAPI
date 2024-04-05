#include "stdafx.h"
#include "DungeonDoor.h"
#include "Camera.h"
#include "BmpMgr.h"
#include "Player.h"

CDungeonDoor::CDungeonDoor()
{
}

CDungeonDoor::~CDungeonDoor()
{
	Release();
}

void CDungeonDoor::Initialize()
{
	m_pFrameKey = L"Dungeon_Door";
	m_vSize = { 138, 89 };
	m_eRender = RENDER_BACKGROUND;
}

int CDungeonDoor::Update()
{
	return 0;
}

void CDungeonDoor::Late_Update()
{
    if(m_bActive)
	    Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
    else
        Set_Collider(m_vPos.x, m_vPos.y, 0, 0);
}

void CDungeonDoor::Render(HDC hDC)
{
	if (m_bActive)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

		GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
			(int)(m_vCameraPos.x - (m_vSize.x * 0.5)), // 복사 받을 위치의 left
			(int)(m_vCameraPos.y - (m_vSize.y * 0.5)),			 // 복사 받을 위치의 top
			(int)m_vSize.x,			 // 복사 받을 가로 길이
			(int)m_vSize.y,			 // 복사 받을 세로 길이
			hMemDC,					// 비트맵을 가지고 있는 dc
			0,						// 출력할 비트맵의 시작 x좌표
			0,						// 출력할 비트맵의 시작 y좌표
			(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
			(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
			RGB(0, 0, 255));	// 제거할 픽셀의 색상 값

		//  RenderCollision(hDC);
	}

}

void CDungeonDoor::OnCollisionEnter(CObj* _pOther)
{
    float   fX(0.f), fY(0.f);
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

    if (pPlayer == nullptr)
    {
        return;
    }
    else
    {
        RECT intersect = {};

        if (::IntersectRect(&intersect, &pPlayer->Get_Collider(), &m_tCollider))
        {
            int w = intersect.right - intersect.left;
            int h = intersect.bottom - intersect.top;

            if (w > h)
            {
                if (intersect.top == m_tCollider.top)
                {
                    pPlayer->Set_PosY(pPlayer->Get_Pos().y - h - 4);
                }
                else
                {
                    pPlayer->Set_PosY(pPlayer->Get_Pos().y + h + 4);
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
                    pPlayer->Set_PosX(w + pPlayer->Get_Pos().x + 4);
                }
            }

        }
    }
}
void CDungeonDoor::Release()
{
}
