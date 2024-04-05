#include "stdafx.h"
#include "StoreNPC.h"
#include "BmpMgr.h"
#include "Camera.h"
CStoreNPC::CStoreNPC()
{
}

CStoreNPC::~CStoreNPC()
{
    Release();
}

void CStoreNPC::Initialize()
{
    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
    m_pFrameKey = L"NPC_Store2";
    m_vSize = { 100.f,95.f };

    m_eRender = RENDER_GAMEOBJECT;
}

int CStoreNPC::Update()
{
    Motion_Change();
    __super::Move_Frame();
    return 0;
}

void CStoreNPC::Late_Update()
{
	
}

void CStoreNPC::Render(HDC hDC)
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
		RGB(192, 192, 192));	// ������ �ȼ��� ���� ��
}

void CStoreNPC::Release()
{
}

void CStoreNPC::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameEnd = 16;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		}
		m_ePreState = m_eCurState;
	}
}
