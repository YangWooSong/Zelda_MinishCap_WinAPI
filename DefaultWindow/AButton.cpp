#include "stdafx.h"
#include "AButton.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Inven.h"
#include "UIWeapon.h"
#include "Inven.h"
CAButton::CAButton() : m_eObjId(ITEM_END), m_pWeapon(nullptr), m_pPlayer(nullptr)
{
}

CAButton::CAButton(float _x, float _y) : m_eObjId(ITEM_END), m_pWeapon(nullptr), m_pPlayer(nullptr)
{
	m_vPos = { _x,_y };
	m_vSize = {36.f,42.f};
}

CAButton::~CAButton()
{
	Release();
}

void CAButton::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Use2.bmp", L"Use2");
	m_eRender = RENDER_UI;
	m_pFrameKey = L"Use2";

	//Inven의 A 아이템 불러오기
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_pWeapon = new CUIWeapon(m_eObjId, VEC2 (m_vPos.x - 50.f, m_vPos.y - 40.f));
}
int CAButton::Update()
{
	m_eObjId = dynamic_cast<CInven*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inven())->Get_AItem();

	dynamic_cast<CUIWeapon*>(m_pWeapon)->Set_ItemId(m_eObjId);

	return 0;
}

void CAButton::Render(HDC hDC)
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

void CAButton::Release()
{
	Safe_Delete(m_pWeapon);
}
