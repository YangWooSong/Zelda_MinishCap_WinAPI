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
}

void CDungeonMonster::Release()
{
}
