#include "stdafx.h"
#include "Boss1.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Player.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "EyeBall.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "LaserBall.h"
#include "SoundMgr.h"
#include "BossFireBall.h"
#include "SceneBoss1.h"

CBoss1::CBoss1() : m_iPatternSelect(0), m_dwTime(GetTickCount()),  m_bMove(false), m_Repeat(0), m_bChangeAttack(true), m_iEyeBallCount(0), m_iLaserBallCount(0)
, m_bDead(false)
{
	m_iHp = 20;
}

CBoss1::~CBoss1()
{
    Release();
}

void CBoss1::Initialize()
{
    m_fSpeed = 1.0f;
	m_vSize = { 300.f, 300.f };

    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
    m_pFrameKey = L"Boss1";

    Set_Collider(0, 0, 0, 0);
    m_eRender = RENDER_GAMEOBJECT;
    m_vLookDir = { 0.f, -1.f };
}

int CBoss1::Update()
{
	Key_Input();


	if (!dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_InvenActive())
	{
		if (m_iHp <= 0)
		{
			m_eCurState = DEAD;
			m_bChangeAttack = false;
		}
		if (m_bDead && m_tFrame.bIsPlayDone)
		{
			dynamic_cast<CSceneBoss1*>(m_pScene)->Set_DoorActive(true);
			return OBJ_DEAD;
		}

		if (m_bChangeAttack == true && m_tFrame.bIsPlayDone)
		{
			if (m_iHp < 10)
			{
				Pattern4_LaserBall();
			}
			else if (m_iHp < 15)
			{
				Pattern1_NormalBullet();
			}
			else if (m_iHp < 20)
			{
				Pattern3_EyeBall();
			}
		}
		else
		{
			if (m_iEyeBallCount <= 0 && m_iLaserBallCount <= 0 && m_iBulletCount <= 0)
				m_bChangeAttack = true;
		}

		if (m_bMove)
		{
			FallowPlayer();
		}

		if (m_bHit)
		{
			m_eCurState = HIT;
			m_bHit = false;
		}
	}

    return OBJ_NOEVENT;
}

void CBoss1::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, 130.f , 180.f);
	
	

    Motion_Change();

	if (m_tFrame.bIsPlayDone && m_eCurState!= DEAD)
		m_eCurState = IDLE;

	if (m_eCurState == DEAD)
		m_bDead = true;

    __super::Move_Frame();

}

void CBoss1::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	if (m_eCurState == DEAD)
	{
		GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
			(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
			(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
			(int)m_vSize.x,			 // 복사 받을 가로 길이
			(int)m_vSize.y,			 // 복사 받을 세로 길이
			hMemDC,					// 비트맵을 가지고 있는 dc
			(int)(m_tFrame.iFrameStart * m_vSize.x),						// 출력할 비트맵의 시작 x좌표
			(int)(m_tFrame.iMotion * m_vSize.y),						// 출력할 비트맵의 시작 y좌표
			(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
			(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
			RGB(255, 0, 255));	// 제거할 픽셀의 색상 값
	}
	else
	{

		GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
			(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
			(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
			(int)m_vSize.x,			 // 복사 받을 가로 길이
			(int)m_vSize.y,			 // 복사 받을 세로 길이
			hMemDC,					// 비트맵을 가지고 있는 dc
			(int)(m_tFrame.iFrameStart * m_vSize.x),						// 출력할 비트맵의 시작 x좌표
			(int)(m_tFrame.iMotion * m_vSize.y),						// 출력할 비트맵의 시작 y좌표
			(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
			(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
			RGB(128, 128, 128));	// 제거할 픽셀의 색상 값
	}

	//RenderCollision(hDC);
}

void CBoss1::Pattern0_Teleport()
{
	//순간이동
	VEC2	teleportList[4] = { VEC2(338.f,268.f),VEC2(878.f,268.f), VEC2(338.f,598.f), VEC2(878.f,598.f)};
	
	m_eCurState = TELEPORT;
	int iTeleportListSelect = rand()%4;
	m_vPos = teleportList[iTeleportListSelect];
	CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
	CSoundMgr::Get_Instance()->PlaySound(L"MC_VaatiReborn_Teleport.wav", SOUND_BOSS, 1.f);


}

void CBoss1::Pattern1_NormalBullet()
{
	Pattern0_Teleport();

	m_eCurState = ATTACK;
	//새로 생성
	m_iBulletCount = 5;

	for (int i = 0; i < 5; ++i)
	{
		m_pBulletList.push_back(CAbstractFactory<CBossFireBall>::Create(m_vPos.x, m_vPos.y, 0 + 45.f * i, this));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pBulletList.back());
	}
	CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
	CSoundMgr::Get_Instance()->PlaySound(L"MC_Vaati_LightBlast_Throw.wav", SOUND_BOSS, 1.f);

	m_bChangeAttack = false;
}

void CBoss1::Pattern3_EyeBall()
{
	m_eCurState = ATTACK;
	
	m_iEyeBallCount = 3;
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EYES);

	Pattern0_Teleport();

	//새로 생성
	for (int i = 0; i < 3; ++i)
	{
		m_pEyeBallList.push_back(CAbstractFactory<CEyeBall>::Create(m_vPos.x, m_vPos.y, 100.f * i, this));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EYES, m_pEyeBallList.back());
	}
	
	m_bChangeAttack = false;
}

void CBoss1::Pattern4_LaserBall()
{
	m_iLaserBallCount = 4;
	m_Repeat++;

	m_eCurState = ATTACK;
	m_bMove = true;

	CObjMgr::Get_Instance()->Delete_ID(OBJ_EYES);

	//새로 생성
	for (int i = 0; i < 4; ++i)
	{
		m_pEyeBallList.push_back(CAbstractFactory<CLaserBall>::Create(m_vPos.x, m_vPos.y, 100.f * i, this));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EYES, m_pEyeBallList.back());
	}	

	m_bChangeAttack = false;
}

void CBoss1::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = true;
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case TELEPORT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case HIT:
			CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"MC_Enemy_Hit.wav", SOUND_BOSS, 1.f);
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 11;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case DEAD:
			CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"MC_Enemy_Kill.wav", SOUND_BOSS, 1.f);
			m_pFrameKey = L"BossExplosion";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			m_vSize = { 250.f, 250.f };
			break;

		}

		m_ePreState = m_eCurState;
	}
}

void CBoss1::Key_Input()
{
	if (CKeyMgr::Get_Instance()->GetKeySate(KEY::E) == KEY_STATE::TAP)
	{
		m_iHp--;
	}
}

void CBoss1::FallowPlayer()
{
	//플레이어한테 이동
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Pos().x - 300.f > m_vPos.x)
	{
		m_vPos.x += m_fSpeed;
	}
	else if (CObjMgr::Get_Instance()->Get_Player()->Get_Pos().x + 300.f < m_vPos.x)
	{
		m_vPos.x -= m_fSpeed;
	}
}

void CBoss1::Change_Attack(int _iSelect)
{
	m_bChangeAttack = false;

	switch (_iSelect)
	{
	case 0:
		Pattern0_Teleport();
		break;
	case 1:
		Pattern1_NormalBullet();
		break;
	case 2:
		if (m_iHp < 10)
			Pattern4_LaserBall();
		else
			Pattern3_EyeBall();
		break;
	default:
		break;
	}
}

void CBoss1::Release()
{
}