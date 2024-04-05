#include "stdafx.h"
#include "Weapon.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Player.h"
#include "Inven.h"
#include "SoundMgr.h"
#include "ObjMgr.h"

CWeapon::CWeapon() : m_bRender(false)
{
}

CWeapon::CWeapon(ITEM_ID _id, VEC2 _v) : m_bRender(true)
{
	m_eItemId = _id;
	m_vPos = _v;
}

CWeapon::~CWeapon()
{
}

void CWeapon::Initialize()
{
    m_eRender = RENDER_EFFECT;
}

int CWeapon::Update()
{
	if (CObjMgr::Get_Instance()->Get_Player()->Get_CurState() == ITEM_GET)
	{
		m_vPos.x = CObjMgr::Get_Instance()->Get_Player()->Get_Pos().x;
		m_vPos.y = CObjMgr::Get_Instance()->Get_Player()->Get_Pos().y-40.f;
	}

	if (m_bDead)
		return OBJ_DEAD;
    return 0;
}

void CWeapon::Late_Update()
{
	if(m_bRender)
		Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void CWeapon::Render(HDC hDC)
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
		break;
	}

	if (m_bRender)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Item");
		m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

		GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
			(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
			(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
			60,			 // 복사 받을 가로 길이
			60,			 // 복사 받을 세로 길이
			hMemDC,					// 비트맵을 가지고 있는 dc
			Render_x,						// 출력할 비트맵의 시작 x좌표
			Render_y,						// 출력할 비트맵의 시작 y좌표
			60,			// 출력할 비트맵의 가로 사이즈
			60,			// 출력할 비트맵의 세로 사이즈
			RGB(0, 0, 255));	// 제거할 픽셀의 색상 값
	}
	
	//RenderCollision(hDC);
}

void CWeapon:: OnCollisionEnter(CObj* _pOther)
{
	float   fX(0.f), fY(0.f);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

	if (pPlayer == nullptr)
		return;
	RECT intersect = {};

	if (::IntersectRect(&intersect, &pPlayer->Get_Collider(), &m_tCollider))
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"58-Get-Item.wav", SOUND_GET_ITEM,1.0f);
		dynamic_cast<CInven*>(pPlayer->Get_Inven())->Set_SlotActive(m_eItemId);
	}
}

void CWeapon::Release()
{
}
