#include "stdafx.h"
#include "Number.h"
#include "BmpMgr.h"

CNumber::CNumber() : m_iNum(0)
{
}

CNumber::~CNumber()
{
    Release();
}

void CNumber::Initialize()
{
    m_eRender = RENDER_UI;
    m_pFrameKey = L"Number";
	m_vSize = { 24.f,24.f };
}

int CNumber::Update()
{
    return 0;
}

void CNumber::Late_Update()
{
}

void CNumber::Render(HDC hDC)
{
	int iRender_x = 24.f;
	int iRender_y = 0;
	if (m_iNum == 10)
	{
		m_pFrameKey = L"Rupe";
		iRender_x =0;
		m_vSize = { 14.f,28.f };
	}
	else if (m_iNum == 11)
	{
		m_pFrameKey = L"Key_UI";
		iRender_x = 0;
		m_vSize = { 33.f,33.f };
	}
	else
		iRender_x *= m_iNum;

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		(int)(m_vPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
		(int)(m_vPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
		(int)m_vSize.x,			 // ���� ���� ���� ����
		(int)m_vSize.y,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		iRender_x,						// ����� ��Ʈ���� ���� x��ǥ
		iRender_y,						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_vSize.x,		// ����� ��Ʈ���� ���� ������
		(int)m_vSize.y,					// ����� ��Ʈ���� ���� ������
		RGB(255, 0, 255));	// ������ �ȼ��� ���� ��

		

}

void CNumber::Release()
{
}
