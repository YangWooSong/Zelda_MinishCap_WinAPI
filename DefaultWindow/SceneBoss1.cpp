#include "stdafx.h"
#include "SceneBoss1.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Wall.h"
#include "AbstractFactory.h"
#include "Boss1.h"
#include "Weapon.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "Door.h"
CSceneBoss1::CSceneBoss1() : m_pBoss(nullptr), m_bDoorActive(false), m_pDoor(nullptr)
{
}

CSceneBoss1::~CSceneBoss1()
{
    Release();
}

void CSceneBoss1::Initialize()
{
	//플레이어 세팅
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(608.f, 700.f);
	CObjMgr::Get_Instance()->Get_Player()->Set_Size(200.f, 200.f);

	//카메라 세팅
	CCamera::Get_Instance()->SetLookAtPos(608.f, 652.5f);
	CCamera::Get_Instance()->SetMaxPos(VEC2(852.5, 652.5f));
	CCamera::Get_Instance()->SetMinPos(VEC2(365.5f, 243.f));
	CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());

	//벽
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(65.f, 448.f, 125.f, 896.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(606.f, 60.f, 1216.f, 133.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1160.f, 448.f, 125.f, 896.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(606.f, 836.f, 1216.f, 133.f));

	m_pFrameKey = L"SceneBoss1";

	//보스
	m_pBoss = CAbstractFactory<CBoss1>::Create(606.f, 310.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pBoss);
	dynamic_cast<CBoss1*>(m_pBoss)->Set_Scene(this);

	//소리
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"52_Vaati_Battle.wav", 1.f);

	m_eRender = RENDER_BACKGROUND;
}

int CSceneBoss1::Update()
{
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

	if (m_bDoorActive)
	{
		m_pFrameKey = L"Boss1_Map2";
		if(m_pDoor == nullptr)
		{
			//포탈
			m_pDoor = CAbstractFactory<CDoor>::Create(608.f, 148.f, 81.f, 43.f, ITEM_Door, &m_bSceneChange);
			CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, m_pDoor);
		}
	}
	if (m_bSceneChange)
	{
	
		list<CObj*>* list = CObjMgr::Get_Instance()->Get_ObjList();
		for (size_t i = OBJ_WALL; i < OBJ_ITEM; ++i)
		{
			for (auto iter = list[i].begin();
				iter != list[i].end(); )
			{
				int		iResult = (*iter)->Update();
				Safe_Delete<CObj*>(*iter);
				iter = list[i].erase(iter);
			}
		}

		CSceneMgr::Get_Instance()->Scene_Change(SC_ENDING);
	}

    return 0;
}

void CSceneBoss1::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneBoss1::Render(HDC hDC)
{
	VEC2 vTemp = { 0,0 };
	m_vCameraRenderPos = CCamera::Get_Instance()->GetRenderPos(vTemp);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	BitBlt(hDC, (int)m_vCameraRenderPos.x, (int)m_vCameraRenderPos.y, 1216, 896, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	CCamera::Get_Instance()->Render(hDC);
}

void CSceneBoss1::Release()
{
}
