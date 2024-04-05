#include "stdafx.h"
#include "MiniGameNPC.h"
#include "BmpMgr.h"
#include "Camera.h"

CMiniGameNPC::CMiniGameNPC()
{
}

CMiniGameNPC::~CMiniGameNPC()
{
	Release();
}

void CMiniGameNPC::Initialize()
{
    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
    m_pFrameKey = L"NPC_MiniGame2";
    m_vSize = { 120.f,120.f };

    m_eRender = RENDER_GAMEOBJECT;
}

int CMiniGameNPC::Update()
{
    Motion_Change();
    __super::Move_Frame();
    return 0;
}

void CMiniGameNPC::Late_Update()
{
}

void CMiniGameNPC::Render(HDC hDC)
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
		RGB(255, 255, 255));	// ������ �ȼ��� ���� ��
}

void CMiniGameNPC::Release()
{
}

void CMiniGameNPC::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameEnd = 12;
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
