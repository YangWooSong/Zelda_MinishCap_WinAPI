#include "stdafx.h"
#include "GageBar.h"
#include "BmpMgr.h"

CGageBar::CGageBar() : m_iStart(0), m_time(GetTickCount()), m_iRenderLength(230), m_bChangeLength(true), m_time2(GetTickCount())
{
}

CGageBar::~CGageBar()
{
    Release();
}

void CGageBar::Initialize()
{
    m_eRender = RENDER_UI;
    m_pFrameKey = L"GageBar_Bar";
}

int CGageBar::Update()
{
	if (m_bIsActive == true)
	{
		//bool �پ��� ����
		if (m_bChangeLength)
		{
			if(m_time2 + 108 < GetTickCount())
			{
				if (m_iRenderLength > 0)
					m_iRenderLength -= 2;
				m_time2 = GetTickCount();
			}
		}
		else 
			m_iRenderLength = 230;
	}

    return 0;
}

void CGageBar::Late_Update()
{
	
}

void CGageBar::Render(HDC hDC)
{
	if(m_bIsActive)
	{
		if (m_time + 300 < GetTickCount())
		{
			if (m_iStart == 0)
				m_iStart = 1;
			else
				m_iStart = 0;

			m_time = GetTickCount();
		}

		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
			m_vPos.x, // ���� ���� ��ġ�� left
			m_vPos.y,			 // ���� ���� ��ġ�� top
			m_iRenderLength,			 // ���� ���� ���� ����
			7,			 // ���� ���� ���� ����
			hMemDC,					// ��Ʈ���� ������ �ִ� dc
			230 * m_iStart,						// ����� ��Ʈ���� ���� x��ǥ
			0,						// ����� ��Ʈ���� ���� y��ǥ
			m_iRenderLength,			// ����� ��Ʈ���� ���� ������
			7,			// ����� ��Ʈ���� ���� ������
			NULL);	// ������ �ȼ��� ���� ��
	}
}

void CGageBar::Release()
{
}
