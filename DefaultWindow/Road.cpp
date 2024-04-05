#include "stdafx.h"
#include "Road.h"
#include "BmpMgr.h"
#include "Camera.h"

CRoad::CRoad() : m_bActive(false)
{
}

CRoad::~CRoad()
{
    Release();
}

void CRoad::Initialize()
{
    m_pFrameKey = L"Dungeon_Road";
    m_vSize = { 96, 192 };

    m_eRender = RENDER_BACKGROUND;
}

int CRoad::Update()
{
	return 0;
}

void CRoad::Late_Update()
{
}

void CRoad::Render(HDC hDC)
{
    if(m_bActive)
    {
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
        m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

        BitBlt(hDC, m_vCameraPos.x - (m_vSize.x * 0.5f), m_vCameraPos.y - (m_vSize.y * 0.5f), m_vSize.x, m_vSize.y, hMemDC, 0, 0, SRCCOPY);
    }
}

void CRoad::Release()
{
}
