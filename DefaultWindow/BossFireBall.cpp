#include "stdafx.h"
#include "BossFireBall.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Boss1.h"
#include "ObjMgr.h"
#include "Player.h"

CBossFireBall::CBossFireBall()
{
}

CBossFireBall::~CBossFireBall()
{
	Release();
}

void CBossFireBall::Initialize()
{
	m_pFrameKey = L"Boss1_Bullet";
	m_vSize = { 50.f, 50.f };
	m_fSpeed = 5.f;

	m_eCurState = IDLE;

	m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };

	Set_Collider(0, 0, 0, 0);
	m_eRender = RENDER_GAMEOBJECT;

	m_iHp = 1;
	m_fAngle = 0.f;
	m_eId = OBJ_BULLET;
}

int CBossFireBall::Update()
{
	if (m_iHp <= 0)
	{
		dynamic_cast<CBoss1*>(m_pTarget)->Minus_BulletCount();
		m_eCurState = DEAD;
		return OBJ_DEAD;
	}

	if (!dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_InvenActive())
	{
		m_vPos.x -= m_fSpeed * (float)cos(3.14 / 180 * m_fAngle);
		m_vPos.y += m_fSpeed * (float)sin((3.14 / 180 * m_fAngle));
	}

	return OBJ_NOEVENT;
}


void CBossFireBall::Late_Update()
{
	if (m_ePreState != m_eCurState)
	{

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.bIsPlayDone = true;

		m_ePreState = m_eCurState;

	}
	Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);

	__super::Move_Frame();
}

void CBossFireBall::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
		(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)(m_tFrame.iFrameStart * m_vSize.x),						// 출력할 비트맵의 시작 x좌표
		(int)(m_tFrame.iMotion * m_vSize.y),						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
		RGB(128, 128, 128));	// 제거할 픽셀의 색상 값

	//RenderCollision(hDC);
}

void CBossFireBall::Release()
{
}
