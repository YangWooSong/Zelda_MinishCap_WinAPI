#include "stdafx.h"
#include "MapObject.h"
#include "BmpMgr.h"
#include "Camera.h"

CMapObject::CMapObject() : m_iNum(0), m_iRenderX(0), m_iRenderY(0)
{
}

CMapObject::~CMapObject()
{
    Release();
}

void CMapObject::Initialize()
{
    m_pFrameKey = L"brazierOn";
    m_vSize = { 48, 48 };

    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };

    m_eRender = RENDER_BACKGROUND;
}

int CMapObject::Update()
{
	return OBJ_NOEVENT;

}

void CMapObject::Late_Update()
{
	if (m_ePreState != m_eCurState)
	{

		switch (m_iNum)
		{
		case 0:
			m_pFrameKey = L"brazierOn";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3 ;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = true;
			m_iRenderX = 48;
			m_iRenderY = 48;
			break;
		case 1:
			m_pFrameKey = L"Dungeon_Obj_Water";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = true;
			m_iRenderX = 228;
			m_iRenderY = 132;
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		}
		m_ePreState = m_eCurState;

	}

//	Set_Collider(m_vPos.x, m_vPos.y, m_iRenderX, m_iRenderY);

	__super::Move_Frame();
}

void CMapObject::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vCameraPos.x - m_iRenderX * 0.5f), // 복사 받을 위치의 left
		(int)(m_vCameraPos.y - m_iRenderY * 0.5f),			 // 복사 받을 위치의 top
		(int)m_iRenderX,			 // 복사 받을 가로 길이
		(int)m_iRenderY,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)(m_tFrame.iFrameStart * m_iRenderX),						// 출력할 비트맵의 시작 x좌표
		(int)(m_tFrame.iMotion * m_iRenderY),						// 출력할 비트맵의 시작 y좌표
		(int)m_iRenderX,			// 출력할 비트맵의 가로 사이즈
		(int)m_iRenderY,			// 출력할 비트맵의 세로 사이즈
		RGB(255, 0, 255));	// 제거할 픽셀의 색상 값

	//RenderCollision(hDC);
}

void CMapObject::Release()
{
}
