#include "stdafx.h"
#include "CopyTile.h"
#include "BmpMgr.h"
#include "Camera.h"

CCopyTile::CCopyTile() : m_bCopy(false)
{
}
CCopyTile::~CCopyTile()
{
    Release();
}
void CCopyTile::Initialize()
{

    m_pFrameKey = L"Floor_Tile";
    m_vSize = { 50, 50 };

    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };

    m_eRender = RENDER_BACKGROUND;
}

int CCopyTile::Update()
{
    return 0;
}

void CCopyTile::Late_Update()
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 12;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.bIsPlayDone = true;

		m_ePreState = m_eCurState;

	}

	Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);

	__super::Move_Frame();
}

void CCopyTile::Render(HDC hDC)
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
		RGB(255, 0, 255));	// ������ �ȼ��� ���� ��

	//RenderCollision(hDC);
}

void CCopyTile::Release()
{
}

void CCopyTile::OnCollisionEnter(CObj* _pOther)
{
	m_bCopy = true;
}

void CCopyTile::OnCollisionExit(CObj* _pOther)
{
	m_bCopy = false;
}
