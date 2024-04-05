#include "stdafx.h"
#include "DungeonMonster.h"
#include "BmpMgr.h"
#include "Camera.h"

CDungeonMonster::CDungeonMonster() : m_iDestinationIndex(0)
{

}

CDungeonMonster::~CDungeonMonster()
{
	Release();
}

void CDungeonMonster::Initialize()
{
	m_pFrameKey = L"Dungeon_Monster";
	m_vSize = { 48, 48 };

	m_eRender = RENDER_GAMEOBJECT;

    DestinationList.push_back(VEC2(1320.f, 3190.f));
    DestinationList.push_back(VEC2(1320.f, 3530.f));
    DestinationList.push_back(VEC2(1420.f, 3530.f));
    DestinationList.push_back(VEC2(1420.f, 3383.f));

    DestinationList.push_back(VEC2(1510.f, 3383.f));
    DestinationList.push_back(VEC2(1510.f, 3285.f));
    DestinationList.push_back(VEC2(1420.f, 3285.f));
    DestinationList.push_back(VEC2(1420.f, 2995.f));

    DestinationList.push_back(VEC2(1320.f, 2995.f));
    DestinationList.push_back(VEC2(1320.f, 3090.f));
    DestinationList.push_back(VEC2(1210.f, 3090.f));
    DestinationList.push_back(VEC2(1210.f, 3190.f));
 
}

int CDungeonMonster::Update()
{
    if (m_iDestinationIndex < 12)
    {
        if (m_vPos.x == DestinationList[m_iDestinationIndex].x && m_vPos.y == DestinationList[m_iDestinationIndex].y)
        {
            ++m_iDestinationIndex;

        }
        else
        {
            if (m_vPos.x != DestinationList[m_iDestinationIndex].x)
            {
                if (m_vPos.x < DestinationList[m_iDestinationIndex].x)
                    m_vPos.x += 1;
                else
                    m_vPos.x -= 1;
            }
            else if (m_vPos.y != DestinationList[m_iDestinationIndex].y)
            {
                if (m_vPos.y < DestinationList[m_iDestinationIndex].y)
                    m_vPos.y += 1;
                else
                    m_vPos.y -= 1;
            }
        }
    }
    else
        m_iDestinationIndex = 0;

	return 0;
}

void CDungeonMonster::Late_Update()
{
	Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void CDungeonMonster::Render(HDC hDC)
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
}

void CDungeonMonster::Release()
{
}
