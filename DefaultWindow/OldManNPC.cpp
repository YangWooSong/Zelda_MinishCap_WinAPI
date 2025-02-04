#include "stdafx.h"
#include "OldManNPC.h"
#include "BmpMgr.h"
#include "Camera.h"

COldManNPC::COldManNPC()
{
}

COldManNPC::~COldManNPC()
{
	Release();
}

void COldManNPC::Initialize()
{
	m_eCurState = IDLE;
	m_pFrameKey = L"NPC_OldMan";
	m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
	m_vSize = {74.f,86.f };

	m_eRender = RENDER_GAMEOBJECT;
}

int COldManNPC::Update()
{
    return 0;
}

void COldManNPC::Late_Update()
{
}

void COldManNPC::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
		(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		0,						// 출력할 비트맵의 시작 x좌표
		0,						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
		RGB(255, 0, 255));	// 제거할 픽셀의 색상 값
}

void COldManNPC::Release()
{
}
