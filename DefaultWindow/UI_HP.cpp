#include "stdafx.h"
#include "UI_HP.h"
#include "BmpMgr.h"

CUI_HP::CUI_HP() : m_iFullCount(0), m_bFull(false)
{
	m_vSize = {30.f, 30.f};
}

CUI_HP::~CUI_HP()
{
	Release();
}

void CUI_HP::Initialize()
{
    m_eRender = RENDER_UI;
    m_pFrameKey = L"LinkHp";
}

int CUI_HP::Update()
{
    return 0;
}

void CUI_HP::Late_Update()
{
}

void CUI_HP::Render(HDC hDC)
{
	int iRender_x = 0;

	if (m_bFull)
	{
		iRender_x = 0;
	}
	else
	{
		switch (m_iFullCount)
		{
		case 0:
			iRender_x = 120;
			break;
		case 1:
			iRender_x = 90;
			break;
		case 2:
			iRender_x = 60;
			break;
		case 3:
			iRender_x = 30;
			break;

		default:
			break;
		}
		
	}


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		(int)(m_vPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
		(int)(m_vPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
		(int)m_vSize.x,			 // ���� ���� ���� ����
		(int)m_vSize.y,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		iRender_x,						// ����� ��Ʈ���� ���� x��ǥ
		0,						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_vSize.x,		// ����� ��Ʈ���� ���� ������
		(int)m_vSize.y,					// ����� ��Ʈ���� ���� ������
		RGB(255, 0, 255));	// ������ �ȼ��� ���� ��

}

void CUI_HP::Release()
{
}
