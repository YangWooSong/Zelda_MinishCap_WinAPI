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

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
		(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
		(int)m_vSize.x,			 // ���� ���� ���� ����
		(int)m_vSize.y,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		0,						// ����� ��Ʈ���� ���� x��ǥ
		0,						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_vSize.x,			// ����� ��Ʈ���� ���� ������
		(int)m_vSize.y,			// ����� ��Ʈ���� ���� ������
		RGB(255, 0, 255));	// ������ �ȼ��� ���� ��
}

void COldManNPC::Release()
{
}
