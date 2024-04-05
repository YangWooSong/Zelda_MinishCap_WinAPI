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

		GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
			(int)(m_vCameraPos.x - (m_vSize.x * 0.5)), // ���� ���� ��ġ�� left
			(int)(m_vCameraPos.y - (m_vSize.y * 0.5)),			 // ���� ���� ��ġ�� top
			(int)m_vSize.x,			 // ���� ���� ���� ����
			(int)m_vSize.y,			 // ���� ���� ���� ����
			hMemDC,					// ��Ʈ���� ������ �ִ� dc
			0,						// ����� ��Ʈ���� ���� x��ǥ
			0,						// ����� ��Ʈ���� ���� y��ǥ
			(int)m_vSize.x,			// ����� ��Ʈ���� ���� ������
			(int)m_vSize.y,			// ����� ��Ʈ���� ���� ������
			RGB(0, 0, 255));	// ������ �ȼ��� ���� ��

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
