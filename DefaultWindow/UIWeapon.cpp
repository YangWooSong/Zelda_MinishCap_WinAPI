#include "stdafx.h"
#include "UIWeapon.h"
#include "BmpMgr.h"

CUIWeapon::CUIWeapon()
{
}

CUIWeapon::CUIWeapon(ITEM_ID _id, VEC2 _v)
{
    m_eItemId = _id;
    m_vPos = _v;
}

CUIWeapon::~CUIWeapon()
{
}

void CUIWeapon::Initialize()
{
    m_eRender = RENDER_UI;
}

int CUIWeapon::Update()
{
    return 0;
}

void CUIWeapon::Late_Update()
{
}

void CUIWeapon::Render(HDC hDC)
{
	int Render_x = 0;
	int Render_y = 0;

	switch (m_eItemId)
	{
	case ITEM_SWORD:
		Render_x = 180;
		break;
	case ITEM_BOW:
		Render_x = 120;
		break;
	case ITEM_SHIELD:
		Render_x = 240;
		break;
	case ITEM_WAND:
		Render_x = 0;
		break;
	case ITEM_POT:
		Render_x = 60;
		break;
	default:
		Render_x = 300;
		break;
	}
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Item");

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		m_vPos.x - m_vSize.x * 0.5f, // 복사 받을 위치의 left
		m_vPos.y - m_vSize.y * 0.5f,			 // 복사 받을 위치의 top
		60,			 // 복사 받을 가로 길이
		60,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		Render_x,						// 출력할 비트맵의 시작 x좌표
		Render_y,						// 출력할 비트맵의 시작 y좌표
		60,			// 출력할 비트맵의 가로 사이즈
		60,			// 출력할 비트맵의 세로 사이즈
		RGB(0, 0, 255));	// 제거할 픽셀의 색상 값
}

void CUIWeapon::Release()
{
}

void CUIWeapon::OnCollisionEnter(CObj* _pOther)
{
}
