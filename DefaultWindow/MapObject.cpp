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

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		(int)(m_vCameraPos.x - m_iRenderX * 0.5f), // ���� ���� ��ġ�� left
		(int)(m_vCameraPos.y - m_iRenderY * 0.5f),			 // ���� ���� ��ġ�� top
		(int)m_iRenderX,			 // ���� ���� ���� ����
		(int)m_iRenderY,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)(m_tFrame.iFrameStart * m_iRenderX),						// ����� ��Ʈ���� ���� x��ǥ
		(int)(m_tFrame.iMotion * m_iRenderY),						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_iRenderX,			// ����� ��Ʈ���� ���� ������
		(int)m_iRenderY,			// ����� ��Ʈ���� ���� ������
		RGB(255, 0, 255));	// ������ �ȼ��� ���� ��

	//RenderCollision(hDC);
}

void CMapObject::Release()
{
}
