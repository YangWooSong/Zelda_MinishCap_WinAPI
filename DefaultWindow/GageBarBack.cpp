#include "stdafx.h"
#include "GageBarBack.h"
#include "AbstractFactory.h"
#include "GageBar.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
CGageBarBack::CGageBarBack() : m_pGageBar(nullptr)
{
}

CGageBarBack::~CGageBarBack()
{
}

void CGageBarBack::Initialize()
{
	m_pGageBar = new CGageBar();
	m_pGageBar->Initialize();

	m_vSize = { 242.f, 19.f };

    m_eRender = RENDER_UI;

}

int CGageBarBack::Update()
{
	if (m_pGageBar)
	{
		m_pGageBar->Set_Pos(m_vPos.x+6, m_vPos.y+6);
		m_pGageBar->Set_IsActive(m_bIsActive);
	}

 	if (dynamic_cast<CGageBar*>(m_pGageBar)->Get_RenderLength() <= 0)
	{
		m_bIsActive = false;
	}

	m_pGageBar->Update();

    return 0;
}

void CGageBarBack::Late_Update()
{
	
	m_pGageBar->Late_Update();
}

void CGageBarBack::Render(HDC hDC)
{
	if(m_bIsActive)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GageBar_BackGround");

		GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
			m_vPos.x, // ���� ���� ��ġ�� left
			m_vPos.y,			 // ���� ���� ��ġ�� top
			m_vSize.x,			 // ���� ���� ���� ����
			m_vSize.y,			 // ���� ���� ���� ����
			hMemDC,					// ��Ʈ���� ������ �ִ� dc
			0,						// ����� ��Ʈ���� ���� x��ǥ
			0,						// ����� ��Ʈ���� ���� y��ǥ
			m_vSize.x,			// ����� ��Ʈ���� ���� ������
			m_vSize.y,			// ����� ��Ʈ���� ���� ������
			RGB(255, 0, 255));	// ������ �ȼ��� ���� ��
	}
	
	if (m_pGageBar)
	{
		m_pGageBar->Render(hDC);
	}
}

void CGageBarBack::Release()
{
}
