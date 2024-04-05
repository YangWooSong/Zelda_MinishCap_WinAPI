#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "Collider.h"
#include "Camera.h"
#include "KeyMgr.h"
#include <iostream>
#include "Inven.h"
#include "PlayerUI.h"
#include "ItemCollider.h"
#include "Boss1.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "Effect.h"
#include "PlayerBullet.h"
#include "Weapon.h"

CPlayer::CPlayer() :m_dwTime(GetTickCount()), m_bInvenActive(false),
m_eAItem(ITEM_SWORD), m_eBItem(ITEM_END), m_eCurItem(ITEM_END),
m_pInven(nullptr), m_pUI(nullptr), m_pItemCollider(nullptr),
m_iDefaultHp(32), m_iCurHp(32), m_bHit(false), m_iRupe(200)
{

}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_fSpeed = 4.f;
	
	m_eCurState = IDLE;
	m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
	m_pFrameKey = L"Player_Down";

	Set_Collider(0, 0, 0, 0);
	m_eRender = RENDER_GAMEOBJECT;
	m_vLookDir = { 0.f, 1.f };

	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEMCOLLIDER, CAbstractFactory<CItemCollider>::Create());
	m_pItemCollider = CObjMgr::Get_Instance()->Get_ItemCollider();
	dynamic_cast<CItemCollider*>(m_pItemCollider)->Set_Target(this);

	m_pItemEffect = CAbstractFactory<CEffect>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, m_pItemEffect);
	m_pItemEffect->Set_Target(this);

	m_eId = OBJ_PLAYER;
}

int CPlayer::Update()

{
	if (m_eCurState == ITEM_GET)
	{
		if (m_tFrame.bIsPlayDone)
			m_eCurState = IDLE;

		return 0;
	}

	Key_Input();

	if(!m_bInvenActive)
	{
		if (m_eCurState == ROLL)
		{
			if (m_vLookDir.x == 1 && m_vLookDir.y == 0)
				m_vPos.x += m_fSpeed + 1.f;
			else if (m_vLookDir.x == -1)
				m_vPos.x -= m_fSpeed + 1.f;
			else if (m_vLookDir.y == 1)
				m_vPos.y += m_fSpeed + 1.f;
			else if (m_vLookDir.y == -1)
				m_vPos.y -= m_fSpeed + 1.f;
		}

		if (m_eCurState == HIT)
		{
			if (m_vLookDir.x == 1 && m_vLookDir.y == 0)
				m_vPos.x -= m_fSpeed + 1.f;
			else if (m_vLookDir.x == -1)
				m_vPos.x += m_fSpeed + 1.f;
			else if (m_vLookDir.y == 1)
				m_vPos.y -= m_fSpeed + 1.f;
			else if (m_vLookDir.y == -1)
				m_vPos.y += m_fSpeed + 1.f;
		}

		if (m_eCurState == ATTACK)
		{

			switch (m_eCurItem)
			{
			case ITEM_SWORD:
				dynamic_cast<CItemCollider*>(m_pItemCollider)->Set_Offset(50.f * m_vLookDir.x, 50.f * m_vLookDir.y);
				if (m_vLookDir.x == 0)
					m_pItemCollider->Set_Size(70.f, 50.f);
				else
					m_pItemCollider->Set_Size(50.f, 70.f);
				break;
			case ITEM_POT:
				dynamic_cast<CEffect*>(m_pItemEffect)->Set_Active(true);
				dynamic_cast<CItemCollider*>(m_pItemCollider)->Set_Offset(70.f * m_vLookDir.x, 70.f * m_vLookDir.y);
				if (m_vLookDir.x == 0)
					m_pItemCollider->Set_Size(40.f, 120.f);
				else
					m_pItemCollider->Set_Size(120.f, 40.f);
				break;
			case ITEM_WAND:
			
				break;
			case ITEM_BOW:
				break;
			case ITEM_SHIELD:
				dynamic_cast<CItemCollider*>(m_pItemCollider)->Set_Offset(30.f * m_vLookDir.x, 30.f * m_vLookDir.y);
				if (m_vLookDir.x == 0)
					m_pItemCollider->Set_Size(40.f, 20.f);
				else
					m_pItemCollider->Set_Size(20.f, 40.f);
				break;
			case ITEM_STRONGSWORD:
				break;
			}
		}
		else
		{
			dynamic_cast<CEffect*>(m_pItemEffect)->Set_Active(false);
			m_pItemCollider->Set_Size(0.f, 0.f);
		}

		Play_Sound();

		if (m_bHit)
		{
			m_eCurState = HIT;
			m_bHit = false;
		}

		if(m_pInven)
		{
			m_eAItem = dynamic_cast<CInven*>(m_pInven)->Get_AItem();
			m_eBItem = dynamic_cast<CInven*>(m_pInven)->Get_BItem();
		}
//
//		//콘솔창 출력
//#ifdef _DEBUG
//
//		if (m_dwTime + 1000 < GetTickCount())
//		{
//			cout << "플레이어 좌표 : " << m_vPos.x << "\t" << m_vPos.y << endl;
//			m_dwTime = GetTickCount();
//		}
//
//#endif
		return OBJ_NOEVENT;
	}
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	if (!m_bInvenActive)
	{
		Set_Collider(m_vPos.x, m_vPos.y, 50.f, 60.f);
		Motion_Change();

		__super::Move_Frame();
	}
}

void CPlayer::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
		(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)(m_tFrame.iFrameStart * 200.f),						// 출력할 비트맵의 시작 x좌표
		(int)(m_tFrame.iMotion * 200.f),						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
		RGB(163, 13, 169));	// 제거할 픽셀의 색상 값

	//RenderCollision(hDC);
}

void CPlayer::Release()
{

}

void CPlayer::Key_Input()
{	
	if (!m_bInvenActive)
	{
		if (CKeyMgr::Get_Instance()->GetKeySate(KEY::RIGHT) == KEY_STATE::HOLD)
		{
			m_vLookDir = { 1,0 };
			m_vPos.x += m_fSpeed;
			m_pFrameKey = L"Player_Right";
			m_eCurState = WALK;
		}
		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::LEFT) == KEY_STATE::HOLD)
		{
			m_vLookDir = { -1,0 };
			m_vPos.x -= m_fSpeed;
			m_pFrameKey = L"Player_Left";
			m_eCurState = WALK;
		}
		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::UP) == KEY_STATE::HOLD)
		{
			m_vLookDir = { 0,-1 };
			m_vPos.y -= m_fSpeed;
			m_pFrameKey = L"Player_Up";
			m_eCurState = WALK;
		}

		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::DOWN) == KEY_STATE::HOLD)
		{
			m_vLookDir = { 0,1 };
			m_vPos.y += m_fSpeed;
			m_pFrameKey = L"Player_Down";
			m_eCurState = WALK;
		}
		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::R) == KEY_STATE::TAP)
		{
			if (m_vLookDir.x == 1 && m_vLookDir.y == 0)
				m_vPos.x += m_fSpeed + 1.f;
			else if (m_vLookDir.x == -1)
				m_vPos.x -= m_fSpeed + 1.f;
			else if (m_vLookDir.y == -1)
				m_vPos.y -= m_fSpeed + 1.f;
			else if (m_vLookDir.y == 1)
				m_vPos.y += m_fSpeed + 1.f;
			m_eCurState = ROLL;
		}
		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::A) == KEY_STATE::TAP)
		{
			m_eCurItem = m_eAItem;
			m_eCurState = ATTACK;
			if(m_eCurItem == ITEM_WAND)
				Shoot_Fire();
		}
		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::B) == KEY_STATE::TAP)
		{
			m_eCurItem = m_eBItem;
			m_eCurState = ATTACK;
			if (m_eCurItem == ITEM_WAND)
				Shoot_Fire();
		}
		else
		{
			if (m_eCurState != DEAD && m_tFrame.bIsPlayDone == true && m_eCurState != ITEM_GET)
			{
				m_eCurState = IDLE;
				m_tFrame.bIsPlayDone = false;
			}
		}

	}
	
	if (CKeyMgr::Get_Instance()->GetKeySate(KEY::I) == KEY_STATE::TAP)
	{
		dynamic_cast<CInven*>(m_pInven)->Set_InvenActive();
		m_bInvenActive = !m_bInvenActive;
	}


}


void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = true;
			break;

		case ROLL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			
			break;

		case ATTACK:
			switch (m_eCurItem)
			{
			case ITEM_SWORD:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 2;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
				m_tFrame.bIsPlayDone = false;
				break;
			case ITEM_BOW:
				m_tFrame.iFrameStart = 0;


				if (m_pFrameKey == L"Player_Down")
					m_tFrame.iFrameEnd = 9;
				else
					m_tFrame.iFrameEnd = 7;

				m_tFrame.iMotion = 6;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
				m_tFrame.bIsPlayDone = false;
				break;
			case ITEM_SHIELD:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 11;
				m_tFrame.iMotion = 7;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
				m_tFrame.bIsPlayDone = false;
				break;
			case ITEM_WAND:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 9;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
				m_tFrame.bIsPlayDone = false;
				break;
			case ITEM_STRONGSWORD:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 12;
				m_tFrame.iMotion = 10;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
				m_tFrame.bIsPlayDone = false;
				break;
			case ITEM_POT:
				if(m_pFrameKey == L"Player_Down")
				{
					m_tFrame.iFrameStart = 0;
					m_tFrame.iFrameEnd = 10;
					m_tFrame.iMotion = 15;
					m_tFrame.dwSpeed = 30;
					m_tFrame.dwTime = GetTickCount();
					m_tFrame.bIsPlayDone = false;
				}
				else
				{
					m_tFrame.iFrameStart = 0;
					m_tFrame.iFrameEnd = 10;
					m_tFrame.iMotion = 13;
					m_tFrame.dwSpeed = 30;
					m_tFrame.dwTime = GetTickCount();
					m_tFrame.bIsPlayDone = false;
				}
				break;
			default:
				break;
			}
			break;

		case HIT:
			if (m_pFrameKey == L"Player_Down")
			{
				m_tFrame.iMotion = 13;
			}
			else
				m_tFrame.iMotion = 12;

			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwSpeed = 180;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case FALL:
			m_pFrameKey = L"Player_Down";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case SIZECHANGE:
			m_pFrameKey = L"Player_Down";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd =12;
			m_tFrame.iMotion = 16;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;

			break;
		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
		
			break;
		case ITEM_GET:
			m_pFrameKey = L"Player_Down";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 11;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;
		}

		m_ePreState = m_eCurState;
	}
}


void CPlayer::OnCollisionExit(CObj* _pOther)
{

}

void CPlayer::OnCollisionStay(CObj* _pOther)
{
	if (dynamic_cast<CWeapon*>(_pOther) != nullptr)
	{
		if (m_eCurState == ITEM_GET && m_tFrame.bIsPlayDone)
		{
			dynamic_cast<CWeapon*>(_pOther)->Set_Render(false);
			dynamic_cast<CWeapon*>(_pOther)->Set_Dead();
		}
	}
}

void CPlayer::OnCollisionEnter(CObj* _pOther)
{
	if (dynamic_cast<CWeapon*>(_pOther) != nullptr)
	{
		m_eCurState = ITEM_GET;
		m_pFrameKey = L"Player_Down";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iMotion = 11;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.bIsPlayDone = false;
	}
}

void CPlayer::Play_Sound()
{
		switch (m_eCurState)
		{ 
		case WALK:
			break;
		case ATTACK:
			switch (m_eCurItem)
			{
			case ITEM_SWORD:
				CSoundMgr::Get_Instance()->PlaySound(L"MC_Link_Sword3.wav", SOUND_PLAYER_ATTACK, 1.f);
				break;
			case ITEM_POT:
				CSoundMgr::Get_Instance()->PlaySound(L"MC_GustJar_Suck1.wav", SOUND_PLAYER_ATTACK, 1.f);
				break;
			case ITEM_WAND:
				break;
			case ITEM_BOW:
				break;
			case ITEM_SHIELD:
				break;
			case ITEM_STRONGSWORD:
				break;
			}
			break;
		case HIT:
			CSoundMgr::Get_Instance()->PlaySound(L"MC_Link_Hurt.wav", SOUND_PLAYER, 1.f);
			break;
		case DEAD:
			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
			CSoundMgr::Get_Instance()->PlaySound(L"link dies.wav", SOUND_PLAYER, 1.f);
			break;
		case ROLL:
			if (m_tFrame.bIsPlayDone == true)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
				CSoundMgr::Get_Instance()->PlaySound(L"MC_Link_RollYar.wav", SOUND_PLAYER, 1.f);
			}
			break;
		case FALL:
			break;
		case SIZECHANGE:
			break;
		case ITEM_GET:
			CSoundMgr::Get_Instance()->StopSound(SOUND_INVEN);
			CSoundMgr::Get_Instance()->PlaySound(L"58 - Get - Item.wav", SOUND_INVEN, 1.f);
			break;
		case ATTACKREADY:
			break;
		}
	
}

void CPlayer::Shoot_Fire()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"MC_Wizzrobe_Shoot_Fire.wav", SOUND_EFFECT, 1.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CPlayerBullet>::Create(m_vPos.x, m_vPos.y, m_vLookDir,this));
}
