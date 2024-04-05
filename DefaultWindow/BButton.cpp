#include "stdafx.h"
#include "BButton.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Inven.h"
#include "UIWeapon.h"
#include "Inven.h"

CBButton::CBButton() : m_eObjId(ITEM_END), m_pWeapon(nullptr), m_pPlayer(nullptr)
{
}

CBButton::CBButton(float _x, float _y) : m_eObjId(ITEM_END), m_pWeapon(nullptr), m_pPlayer(nullptr)
{
	m_vPos = { _x,_y };
	m_vSize = {36.f,42.f};
}

CBButton::~CBButton()
{
	Release();
}

void CBButton::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Use1.bmp", L"Use1");
	m_eRender = RENDER_UI;
	m_pFrameKey = L"Use1";

	//Inven의 B 아이템 불러오기
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_pWeapon = new CUIWeapon(m_eObjId, VEC2(m_vPos.x - 50.f, m_vPos.y - 40.f));
}

int CBButton::Update()
{
	m_eObjId = dynamic_cast<CInven*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inven())->Get_BItem();

	dynamic_cast<CUIWeapon*>(m_pWeapon)->Set_ItemId(m_eObjId);
	return 0;
}

void CBButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
		(int)(m_vPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		0,						// 출력할 비트맵의 시작 x좌표
		0,						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,		// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,					// 출력할 비트맵의 세로 사이즈
		RGB(255, 0, 255));	// 제거할 픽셀의 색상 값


	m_pWeapon->Render(hDC);
}

void CBButton::Release()
{
	Safe_Delete(m_pWeapon);
}
