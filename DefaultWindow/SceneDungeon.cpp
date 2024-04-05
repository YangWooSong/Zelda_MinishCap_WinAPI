#include "stdafx.h"
#include "SceneDungeon.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "Wall.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "CCeilling.h"
#include "AbstractFactory.h"
#include "MapObject.h"
#include "Button.h"
#include "Key.h"
#include "KeyRock.h"
#include "CopyTile.h"
#include "KeyMgr.h"
#include "Player.h"
#include "CopyPlayer.h"
#include "MovingRock.h"
#include "Road.h"
#include "MovingFloor.h"
#include "DungeonMonster.h"
#include "Brazier.h"
#include "DungeonDoor.h"
#include "SieldMonster.h"
#include "Door.h"
#include "PlayerUI.h"
#include "GageBar.h"
#include "GageBarBack.h"
CSceneDungeon::CSceneDungeon() : m_bBossScene(false), m_bVillageScene(false), m_pUI(nullptr)
, m_bLeftKeyActive(false), m_bRightKeyActive(false), m_iKeyCount (0), m_pLeftKey(nullptr), m_pRightKey(nullptr)
, m_pKeyRock1(nullptr), m_pKeyRock2(nullptr), m_iPosCount(0), m_dwTime(GetTickCount()), m_pRoadButton(nullptr)
, m_pRoad(nullptr), m_pMovingRock(nullptr), m_pDoor(nullptr), m_bActiveDoor(true), m_pSieldMonster(nullptr), m_bActiveShieldMonster(false)
{
}

CSceneDungeon::~CSceneDungeon()
{
    Release();
}

void CSceneDungeon::Initialize()
{
	//플레이어
    CObjMgr::Get_Instance()->Get_Player()->Set_Pos(887.f, 5088.f);
    CObjMgr::Get_Instance()->Get_Player()->Set_Size(200.f, 200.f);

	//카메라
    CCamera::Get_Instance()->SetLookAtPos(887.f, 4988.f);
    CCamera::Get_Instance()->SetMaxPos(VEC2(1412.f, 4988.f));
    CCamera::Get_Instance()->SetMinPos(VEC2(365.5f,235.f));
    CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());

	//입구쪽 벽
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(705.f,5180.f, 310.f, 90.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1071.f, 5180.f, 310.f, 90.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(705.f, 4700.f, 310.f, 290.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1071.f, 4700.f, 310.f, 290.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(581.f, 4977.f, 90.f, 330.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1200.f, 4977.f, 90.f, 330.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(646.f, 4864.f,50.f, 50.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(646.f, 5107.f,50.f, 50.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1125.f, 4864.f, 50.f, 50.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1125.f, 5107.f, 50.f, 50.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(575.f, 4225.f, 90.f, 680.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1208.f, 4225.f, 90.f, 680.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(480.f, 3747.f, 747.f, 285.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1300.f, 3747.f, 747.f, 285.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(140.f, 3170.f, 95.f, 870.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1630.f, 3170.f, 95.f, 870.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(980.f, 4053.f, 336.f, 45.f));

	//위쪽 벽
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1265.f, 2580.f, 680.f, 270.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(510.f, 2580.f, 680.f, 270.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1065.f, 2060.f, 108.f, 795.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(711.f, 2060.f, 108.f, 795.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(965.f, 2060.f, 90.f, 465.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(805.f, 2060.f, 90.f, 465.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1075.f, 1580.f, 317.f, 170.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(690.f, 1580.f, 317.f, 170.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(520.f, 910.f, 605.f, 375.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1245.f, 910.f, 605.f, 375.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1253.f, 1290.f, 100.f, 415.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(515.f, 1290.f, 100.f, 415.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(180.f, 411.f, 100.f, 655.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1595.f, 411.f, 100.f, 655.f));

	//왼쪽
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(290.f, 2786.f, 10.f, 140.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(570.f, 2786.f, 10.f, 140.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(343.f, 2853.f, 90.f, 10.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(523.f, 2853.f, 90.f, 10.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(383.f, 2836.f, 9.f, 25.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(480.f, 2836.f, 9.f, 25.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(745.f, 2900.f, 50.f, 335.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(700.f, 3140.f, 50.f, 240.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(695.f, 3480.f, 50.f, 240.f));

	//왼쪽 돌
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(357.f, 3045.f, 140.f,45.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(357.f, 3284.f, 45.f,420.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(285.f, 3380.f, 90.f, 45.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(430.f, 3190.f, 90.f, 45.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(620.f, 3045.f, 90.f, 45.f));

	//오른쪽
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1480.f, 2786.f, 10.f, 140.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1206.f, 2786.f, 10.f, 140.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1433.f, 2853.f, 90.f, 10.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1253.f, 2853.f, 90.f, 10.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1393.f, 2836.f, 9.f, 25.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1296.f, 2836.f, 9.f, 25.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1030.f, 2900.f, 50.f, 335.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1080.f, 3140.f, 50.f, 240.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1080.f, 3480.f, 50.f, 240.f));
	
	//오른쪽 돌
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1365.f, 3250.f, 45.f, 450.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1365.f, 3576.f, 45.f, 45.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1440.f, 3335.f, 90.f, 45.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1295, 3140.f, 90.f, 45.f));

	//화로
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(795.f, 3527.f, 40.f, 25.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(795.f, 3377.f, 40.f, 25.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(795.f, 3230.f, 40.f, 25.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(980.f, 3527.f, 40.f, 25.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(980.f, 3377.f, 40.f, 25.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(980.f, 3230.f, 40.f, 25.f));

	//석상
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(965.f, 3050.f, 75.f, 132.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(810.f, 3050.f, 75.f, 132.f));

	//천장
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(815.f, 5187.f, SC_DUNGEON, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(815.f, 4607.f, SC_DUNGEON, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(815.f, 3650.f, SC_DUNGEON, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(820.f, 2497.f, SC_DUNGEON, 2));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(817.f,1536.f, SC_DUNGEON, 3));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(767.f, 820.f, SC_DUNGEON, 4));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(780.f, 2130.f, SC_DUNGEON, 5));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(780.f, 1938.f, SC_DUNGEON, 5));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(238.f, 3025.f, SC_DUNGEON, 6));

	//물건들
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(791.f, 3528.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(791.f, 3382.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(791.f, 3240.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(984.f, 3528.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(984.f, 3382.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(984.f, 3240.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(360.f, 2805.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(504.f, 2805.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(1272.f, 2805.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(1416.f, 2805.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(885.f, 2373.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CMapObject>::Create(885.f, 1755.f, 1));
	

	//버튼
	m_LeftButtonList.push_back(CAbstractFactory<CButton>::Create(504.f, 2949.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_LeftButtonList.back());
	m_LeftButtonList.push_back(CAbstractFactory<CButton>::Create(312.f, 2950.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_LeftButtonList.back());
	m_LeftButtonList.push_back(CAbstractFactory<CButton>::Create(312.f, 2904.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_LeftButtonList.back());

	m_RightButtonList.push_back(CAbstractFactory<CButton>::Create(1270.f, 2949.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_RightButtonList.back());
	m_RightButtonList.push_back(CAbstractFactory<CButton>::Create(1462.f, 2950.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_RightButtonList.back());
	m_RightButtonList.push_back(CAbstractFactory<CButton>::Create(1462.f, 2904.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_RightButtonList.back());

	m_pRoadButton = CAbstractFactory<CButton>::Create(648.f, 4535.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_pRoadButton);

	//화로 
	m_BrazierList.push_back(CAbstractFactory<CBrazier>::Create(598.f, 1463.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_BrazierList.back());
	m_BrazierList.push_back(CAbstractFactory<CBrazier>::Create(598.f, 1128.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_BrazierList.back());
	m_BrazierList.push_back(CAbstractFactory<CBrazier>::Create(1174.f, 1128.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_BrazierList.back());
	m_BrazierList.push_back(CAbstractFactory<CBrazier>::Create(1174.f, 1463.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_BrazierList.back());

	
	//바닥
	m_pRoad = CAbstractFactory<CRoad>::Create(720.f, 4223.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_pRoad);
	m_pMovingFloor =  CAbstractFactory<CMovingFloor>::Create(360.f, 3430.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_pMovingFloor);

	//밀리는 돌
	m_pMovingRock = CAbstractFactory<CMovingRock>::Create(720.f, 4536.f, this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, m_pMovingRock);
	
	//열쇠
	m_pLeftKey = CAbstractFactory<CKey>::Create(427.f, 2798.f,this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_pLeftKey);
	m_pRightKey = CAbstractFactory<CKey>::Create(1343.f, 2798.f, this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_pRightKey);

	//열쇠 돌
	m_pKeyRock1 = CAbstractFactory<CKeyRock>::Create(888.f, 3093.f,this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_pKeyRock1);
	m_pKeyRock2 = CAbstractFactory<CKeyRock>::Create(888.f, 3046.f, this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_pKeyRock2);

	//분신술 바닥
	m_CopyTileList.push_back(CAbstractFactory<CCopyTile>::Create(458.f, 3577.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_CopyTileList.back());
	m_CopyTileList.push_back(CAbstractFactory<CCopyTile>::Create(263.f, 3575.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_CopyTileList.back());
	m_CopyTileList.push_back(CAbstractFactory<CCopyTile>::Create(263.f, 3525.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_CopyTileList.back());

	m_CopyTileList.push_back(CAbstractFactory<CCopyTile>::Create(1270.f, 3577.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_CopyTileList.back());
	m_CopyTileList.push_back(CAbstractFactory<CCopyTile>::Create(1463.f, 3575.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_CopyTileList.back());
	m_CopyTileList.push_back(CAbstractFactory<CCopyTile>::Create(1463.f, 3525.f, this));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_CopyTileList.back());

	//문
	m_pDoor = CAbstractFactory<CDungeonDoor>::Create(883.f, 1060.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, m_pDoor);

	//몬스터
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CDungeonMonster>::Create(1300.f, 3190.f));
	m_pSieldMonster = CAbstractFactory<CSieldMonster>::Create(880.f, 1250.f, this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pSieldMonster);

	//포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDoor>::Create(888.f, 220.f, 50.f, 50.f, ITEM_Door, &m_bBossScene));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDoor>::Create(888.f, 5165.f, 50.f, 50.f, ITEM_Door, &m_bVillageScene));

	//소리
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"47_Royal_Crypt.wav", 1.f);

	m_pFrameKey = L"Dungeon_Ver2";

	m_eRender = RENDER_BACKGROUND;

	m_pUI = CObjMgr::Get_Instance()->Get_UI();

	
}

int CSceneDungeon::Update()
{
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

	//열쇠 UI On
	dynamic_cast<CPlayerUI*>(m_pUI)->Set_KeyUiActive(true);
	dynamic_cast<CPlayerUI*>(m_pUI)->Set_KeyCount(m_iKeyCount);
	//길 생성
	if (dynamic_cast<CButton*>(m_pRoadButton)->Get_Active())
	{
		if(dynamic_cast<CRoad*>(m_pRoad)->Get_Active()==false)
			CSoundMgr::Get_Instance()->PlaySoundW(L"secret.wav", SOUND_EFFECT2, 1.f);
		dynamic_cast<CRoad*>(m_pRoad)->Set_Active(true);
	}
	else
	{
		dynamic_cast<CRoad*>(m_pRoad)->Set_Active(false);
	}

	//분신 삭제
	if (m_dwTime + 12830 < GetTickCount() && CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->size() > 1)
	{
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->back()->Set_Dead();
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->back()->Set_Dead();
	}

	//씬 전환
	if (m_bBossScene)	    //씬 넘어가기
	{
		list<CObj*>* list = CObjMgr::Get_Instance()->Get_ObjList();

		for (size_t i = OBJ_WALL; i <= OBJ_ITEM; ++i)
		{
			for (auto iter = list[i].begin();
				iter != list[i].end(); )
			{
				Safe_Delete<CObj*>(*iter);
				iter = list[i].erase(iter);
			}
	 	}
		dynamic_cast<CPlayerUI*>(m_pUI)->Set_KeyUiActive(false);
		CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS1);
		return 0;
	}

	if (m_bVillageScene)	  
	{
		list<CObj*>* list = CObjMgr::Get_Instance()->Get_ObjList();

		for (size_t i = OBJ_WALL; i <= OBJ_ITEM; ++i)
		{
			for (auto iter = list[i].begin();
				iter != list[i].end(); )
			{
				Safe_Delete<CObj*>(*iter);
				iter = list[i].erase(iter);
			}
		}

		CSceneMgr::Get_Instance()->Scene_Change(SC_FOREST);
		return 0;
	}
	//열쇠 활성화
	Active_LeftKey();
	Active_RightKey();

	if(m_bActiveShieldMonster == false)
		Activate_Monster();

	Active_Door();
	
	Key_Input();


	return 0;
}

void CSceneDungeon::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
}

void CSceneDungeon::Render(HDC hDC)
{
    VEC2 vTemp = { 0,0 };
    m_vCameraRenderPos = CCamera::Get_Instance()->GetRenderPos(vTemp);
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    BitBlt(hDC, (int)m_vCameraRenderPos.x, (int)m_vCameraRenderPos.y, 1776, 5232, hMemDC, 0, 0, SRCCOPY);

    CObjMgr::Get_Instance()->Render(hDC);
    CCamera::Get_Instance()->Render(hDC);
}

void CSceneDungeon::Release()
{
}

void CSceneDungeon::Activate_Monster()
{
	int iCount = 0;
	for (auto& iter : m_BrazierList)
	{
		if (dynamic_cast<CBrazier*>(iter)->Get_Active())
			++iCount;
	}

	if (iCount >= 4 )
	{
		m_bActiveShieldMonster = true;
		dynamic_cast<CSieldMonster*>(m_pSieldMonster)->Set_Active(true);
	}
}

void CSceneDungeon::Active_LeftKey()
{
	//버튼 3개 동시 활성화시 열쇠 드랍
	int iCount = 0;
	for (auto& iter : m_LeftButtonList)
	{
		if (dynamic_cast<CButton*>(iter)->Get_Active())
			++iCount;
	}

	if(iCount == 3)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"secret.wav", SOUND_EFFECT, 1.f);
		dynamic_cast<CKey*>(m_pLeftKey)->Set_Active(true);
	}
}

void CSceneDungeon::Active_RightKey()
{
	//버튼 3개 동시 활성화시 열쇠 드랍
	int iCount = 0;
	for (auto& iter : m_RightButtonList)
	{
		if (dynamic_cast<CButton*>(iter)->Get_Active())
			++iCount;
	}

	if (iCount == 3)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"secret.wav", SOUND_EFFECT, 1.f);
		dynamic_cast<CKey*>(m_pRightKey)->Set_Active(true);
	}

}

void CSceneDungeon::Key_Input()
{
	if (CKeyMgr::Get_Instance()->GetKeySate(KEY::SPACE) == KEY_STATE::HOLD)
	{
		dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Set_GageActive(true);
		dynamic_cast<CGageBar*>(dynamic_cast<CGageBarBack*>(dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Get_m_pGageBar())->Get_bar())->Set_m_bChangeLength(false);

		//밟은 타일의 좌표 저장
		for (int i = 0; i < 6; ++i)
		{
			if (dynamic_cast<CCopyTile*>(m_CopyTileList[i])->Get_IsCopy())
			{
				if(m_iPosCount < 3)
				{
					m_vCopyPos[m_iPosCount] = m_CopyTileList[i]->Get_Pos();
					m_iPosCount++ ;
					dynamic_cast<CCopyTile*>(m_CopyTileList[i])->Set_IsCaopyFalse();
				}
			}
		}
	}
	if (CKeyMgr::Get_Instance()->GetKeySate(KEY::SPACE) == KEY_STATE::AWAY)
	{	
		dynamic_cast<CGageBar*>(dynamic_cast<CGageBarBack*>(dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Get_m_pGageBar())->Get_bar())->Set_m_bChangeLength(true);
		//플레이어 생성
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CCopyPlayer>::Create(m_vCopyPos[0].x, m_vCopyPos[0].y , 0 , CObjMgr::Get_Instance()->Get_Player()));
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CCopyPlayer>::Create(m_vCopyPos[1].x, m_vCopyPos[1].y, 0, CObjMgr::Get_Instance()->Get_Player()));
		
		//저장한 좌표 초기화
		m_vCopyPos[1] = {};
		m_vCopyPos[0] = {};
		m_iPosCount = 0;
		m_dwTime = GetTickCount();

		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"MC_Sword_Gleam.wav", SOUND_EFFECT, 1.f);
		
	}
}

void CSceneDungeon::Active_Door()
{
	if (!m_bActiveDoor)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySoundW(L"bomb explode.wav", SOUND_EFFECT, 1.f);
		dynamic_cast<CDungeonDoor*>(m_pDoor)->Set_Active(false);
		m_bActiveDoor = true;;
	}
	
}
