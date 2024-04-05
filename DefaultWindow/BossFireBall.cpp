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

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
		(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
		(int)m_vSize.x,			 // ���� ���� ���� ����
		(int)m_vSize.y,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)(m_tFrame.iFrameStart * m_vSize.x),						// ����� ��Ʈ���� ���� x��ǥ
		(int)(m_tFrame.iMotion * m_vSize.y),						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_vSize.x,			// ����� ��Ʈ���� ���� ������
		(int)m_vSize.y,			// ����� ��Ʈ���� ���� ������
		RGB(128, 128, 128));	// ������ �ȼ��� ���� ��

	//RenderCollision(hDC);
}

void CBossFireBall::Release()
{
}
