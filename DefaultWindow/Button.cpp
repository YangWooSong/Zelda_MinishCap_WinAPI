#include "stdafx.h"
#include "Button.h"
#include "BmpMgr.h"
#include "Camera.h"

CButton::CButton() : m_bActive(false)
{
}

CButton::~CButton()
{
}

void CButton::Initialize()
{
    m_pFrameKey = L"Button";
    m_vSize = { 48, 48 };

    m_eCurState = IDLE;

    m_eRender = RENDER_BACKGROUND;
}

int CButton::Update()
{
    return 0;
}

void CButton::Late_Update()
{

	Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);

	__super::Move_Frame();
}

void CButton::Render(HDC hDC)
{
	int Render_x = 0;
	int Render_y = 0;


	if (m_bActive)
	{
		Render_x = 48;
	}
	else
	{
		Render_x = 0;
	}

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	BitBlt(  hDC , m_vCameraPos.x - (m_vSize.x*0.5f), m_vCameraPos.y- (m_vSize.y * 0.5f), m_vSize.x, m_vSize.y, hMemDC, Render_x, Render_y, SRCCOPY);
	//RenderCollision(hDC);

}

void CButton::OnCollisionEnter(CObj* _pOther)
{
	m_bActive = true;
}
void CButton::OnCollisionExit(CObj* _pOther)
{
    m_bActive = false;
}
void CButton::Release()
{
}
