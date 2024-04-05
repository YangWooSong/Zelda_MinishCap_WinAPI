#include "stdafx.h"
#include "SieldMonster.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "SoundMgr.h"
#include <ctime>
#include "AbstractFactory.h"
#include "ShieldCollider.h"
#include "SceneDungeon.h"

CSieldMonster::CSieldMonster() : m_pPlayer(nullptr), m_bChangeState(true), m_bActive(false)
{
}

CSieldMonster::~CSieldMonster()
{
    Release();
}

void CSieldMonster::Initialize()
{
	m_fSpeed = 1.f;

	m_eCurState = IDLE;
	m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
	m_pFrameKey = L"Monster_Shield";
	m_vSize = { 300.f,300.f };
	Set_Collider(0, 0, 0, 0);
	m_eRender = RENDER_GAMEOBJECT;
	m_vLookDir = { 0.f, 1.f };
	m_iHp = 5;
	m_ePreState = SHIELD;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	m_pShieldCollider = CAbstractFactory<CShieldCollider>::Create(0,0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pShieldCollider);
	m_pShieldCollider->Set_Target(this);
}

int CSieldMonster::Update()
{
	if(m_bActive)
	{
		srand(unsigned(time(NULL)));
	
		if (m_iHp < 0)
		{
			m_eCurState = DEAD;
		
		}
		if (m_tFrame.bIsPlayDone && m_bDead)
		{
			dynamic_cast<CSceneDungeon*>(m_pScene)->Set_DoorActiveFalse();
			return OBJ_DEAD;
		}
	
	
		Set_Collider(m_vPos.x, m_vPos.y, 100.f, 100.f);
	}

	if(m_eCurState == ATTACK && m_tFrame.iFrameStart == 5)
		CSoundMgr::Get_Instance()->PlaySoundW(L"MC_Link_Sword.wav", SOUND_MONSTER, 1.f);
	return OBJ_NOEVENT;
}

void CSieldMonster::Late_Update()
{
	if(m_bActive)
	{
		int iSelect = rand() % 2;

		//공격과 방어를 번갈아 실행
		if (m_tFrame.bIsPlayDone)
		{
			Set_Dir();

			if (m_bChangeState)
			{
				if (iSelect == 0)
				{

					m_eCurState = ATTACK;
				}
				/*	else if (iSelect == 1)
					{
						m_eCurState = SHIELD;
					}*/
				else
				{
					dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Active(false);
					m_eCurState = IDLE;
				}
			}
		}

		Motion_Change();
		Set_SwordCollider();

		if (m_eCurState == DEAD)
		{
			m_bDead = true;
		}
		__super::Move_Frame();
	}
}

void CSieldMonster::Render(HDC hDC)
{
	if(m_bActive)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

		GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
			(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
			(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
			(int)m_vSize.x,			 // 복사 받을 가로 길이
			(int)m_vSize.y,			 // 복사 받을 세로 길이
			hMemDC,					// 비트맵을 가지고 있는 dc
			(int)(m_tFrame.iFrameStart * 300.f),						// 출력할 비트맵의 시작 x좌표
			(int)(m_tFrame.iMotion * 300.f),						// 출력할 비트맵의 시작 y좌표
			(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
			(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
			RGB(163, 13, 169));	// 제거할 픽셀의 색상 값

		//RenderCollision(hDC);
	}
}

void CSieldMonster::Release()
{
}

void CSieldMonster::Set_Dir()
{
	if (m_vPos.x + 100.f < m_pPlayer->Get_Pos().x)
	{
		m_eCurState = IDLE;
		m_vLookDir = { 1.f,0.f };
		m_vPos.x += m_fSpeed;
		m_bChangeState = false;
	}
	else if (m_vPos.x - 100.f > m_pPlayer->Get_Pos().x)
	{
		m_eCurState = IDLE;
		m_vLookDir = { -1.f,0.f };
		m_vPos.x -= m_fSpeed;
		m_bChangeState = false;
	}
	if (m_vPos.y + 100.f < m_pPlayer->Get_Pos().y)
	{
		m_eCurState = IDLE;
		m_vLookDir = { 0.f , 1.f };
		m_vPos.y += m_fSpeed;
		m_bChangeState = false;
	}
	else if (m_vPos.y - 100.f > m_pPlayer->Get_Pos().y)
	{
		m_eCurState = IDLE;
		m_vLookDir = { 0.f , -1.f };
		m_vPos.y -= m_fSpeed;
		m_bChangeState = false;
	}
	else
		m_bChangeState = true;
}

void CSieldMonster::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			if (m_vLookDir.x == 1)		//오른쪽
			{
				m_tFrame.iMotion = 10;
			}
			else if (m_vLookDir.x == -1)	//왼쪽
			{
				m_tFrame.iMotion = 9;
			}
			else if (m_vLookDir.y == 1) //아래
			{
				m_tFrame.iMotion =11;
			}
			else if (m_vLookDir.y == -1) //위
			{
				m_tFrame.iMotion = 8;
			}
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameStart = 7;
			m_tFrame.dwSpeed = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case ATTACK:
			if (m_vLookDir.x == 1)		//오른쪽
			{
		
				m_tFrame.iMotion = 14;
				m_tFrame.iFrameEnd = 9;
			}
			else if (m_vLookDir.x == -1)	//왼쪽
			{
				m_tFrame.iMotion = 13;
				m_tFrame.iFrameEnd = 9;
			}
			else if (m_vLookDir.y == 1) //아래
			{
				m_tFrame.iMotion = 15;
				m_tFrame.iFrameEnd = 11;
			}
			else if (m_vLookDir.y == -1) //위
			{
				m_tFrame.iMotion = 12;
				m_tFrame.iFrameEnd = 11;
			}
			
			m_tFrame.iFrameStart = 0;
			m_tFrame.dwSpeed = 200.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case HIT:
			CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"MC_Enemy_Hit.wav", SOUND_MONSTER, 1.f);
			if (m_vLookDir.x == 1)		//오른쪽
			{
				m_tFrame.iMotion = 20;
			}
			else if (m_vLookDir.x == -1)	//왼쪽
			{
				m_tFrame.iMotion = 19;
			}
			else if (m_vLookDir.y == 1) //아래
			{
				m_tFrame.iMotion = 21;
			}
			else if (m_vLookDir.y == -1) //위
			{
				m_tFrame.iMotion = 18;
			}
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case SHIELD:
			if (m_vLookDir.x == 1)		//오른쪽
			{
				m_tFrame.iMotion = 10;
				m_tFrame.iFrameEnd = 8;
			}
			else if (m_vLookDir.x == -1)	//왼쪽
			{
				m_tFrame.iMotion = 9;
				m_tFrame.iFrameEnd = 8;
			}
			else if (m_vLookDir.y == 1) //아래
			{
				m_tFrame.iMotion = 11;
				m_tFrame.iFrameEnd = 7;
			}
			else if (m_vLookDir.y == -1) //위
			{
				m_tFrame.iMotion = 8;
				m_tFrame.iFrameEnd = 7;
			}

			m_tFrame.iFrameStart = 0;
			m_tFrame.dwSpeed = 200.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case DEAD:
			CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"MC_Enemy_Hit.wav", SOUND_MONSTER, 1.f);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 16;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;

			break;

		}

		m_ePreState = m_eCurState;
	}
}

void CSieldMonster::Set_SwordCollider()
{
	if(m_eCurState == ATTACK && m_tFrame.iFrameStart > 4)
	{
		dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Active(true);
		if (m_vLookDir.x == 1)		//오른쪽
		{

			dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Offset(80.f, 10.f);
			dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Size(100.f, 40.f);
		}
		else if (m_vLookDir.x == -1)	//왼쪽
		{
			dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Offset(-80.f, -10.f);
			dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Size(100.f, 40.f);
		}
		else if (m_vLookDir.y == 1) //아래
		{
			dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Offset(-10.f, 80.f);
			dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Size(40.f, 100.f);
		}
		else if (m_vLookDir.y == -1) //위
		{
			dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Offset(10.f, -60.f);
			dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Size(40.f, 100.f);
		}
	}
	else
		dynamic_cast<CShieldCollider*>(m_pShieldCollider)->Set_Active(false);

}
