#include "stdafx.h"
#include "CCeilling.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
int     m_iRenderX;
CCeilling::CCeilling():m_eSceneId(SC_HOUSE), m_iNum(0), m_iRenderX(0), m_iRenderY(0)
{
}
CCeilling::~CCeilling()
{
}
void CCeilling::Initialize()
{

	m_eRender = RENDER_CEILLING;
	m_pFrameKey = L"SceneHouse_Ceilling";
}

int CCeilling::Update()
{
	switch (m_eSceneId)
	{
	case SC_HOUSE:
		m_pFrameKey = L"SceneHouse_Ceilling";
		m_iRenderX = 114;
		m_iRenderY = 293;
		break;
	case SC_VILLAGE:
		switch (m_iNum)
		{
		case 0:
			m_pFrameKey = L"Town_0";
			m_iRenderX = 432;
			m_iRenderY = 180;
			break;
		case 1:
			m_pFrameKey = L"Town_Wood";
			m_iRenderX = 390;
			m_iRenderY = 23;
			break;
		case 2:
			m_pFrameKey = L"TownMark";
			m_iRenderX = 312;
			m_iRenderY = 117;
			break;
		}
		break;
	case SC_DUNGEON:
		switch (m_iNum)
		{
		case 0:
			m_pFrameKey = L"Dungeon0";
			m_iRenderX = 144;
			m_iRenderY = 48;
			break;
		case 1:
			m_pFrameKey = L"Dungeon1";
			m_iRenderX = 144;
			m_iRenderY = 192;
			break;
		case 2:
			m_pFrameKey = L"Dungeon2";
			m_iRenderX = 144;
			m_iRenderY = 192;
			break;
		case 3:
			m_pFrameKey = L"Dungeon3";
			m_iRenderX = 132;
			m_iRenderY = 96;
			break;
		case 4:
			m_pFrameKey = L"Dungeon4";
			m_iRenderX = 240;
			m_iRenderY = 192;
			break;
		case 5:
			m_pFrameKey = L"Dungeon5";
			m_iRenderX = 200;
			m_iRenderY = 30;
			break;
		case 6:
			m_pFrameKey = L"Dungeon6";
			m_iRenderX = 242;
			m_iRenderY = 478;
			break;
		}
		break;
	case SC_BOSS1:
		break;
	case SC_ENDING:
		break;
	}
    return 0;
}

void CCeilling::Late_Update()
{
}

void CCeilling::Render(HDC hDC)
{
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		(int)(m_vCameraPos.x), // ���� ���� ��ġ�� left
		(int)(m_vCameraPos.y ),			 // ���� ���� ��ġ�� top
		(int)m_iRenderX,			 // ���� ���� ���� ����
		(int)m_iRenderY,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		0,						// ����� ��Ʈ���� ���� x��ǥ
		0,						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_iRenderX,			// ����� ��Ʈ���� ���� ������
		(int)m_iRenderY,			// ����� ��Ʈ���� ���� ������
		RGB(255, 0, 255));	// ������ �ȼ��� ���� ��
}

void CCeilling::Release()
{
}
