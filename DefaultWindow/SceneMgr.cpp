#include "stdafx.h"
#include "SceneMgr.h"

#include "SceneLogo.h"
#include "SceneHouse.h"
#include "SceneForest.h"
#include "SceneDungeon.h"
#include "SceneBoss1.h"
#include "SceneVillage.h"
#include "SceneStore.h"
#include "SceneEnding.h"
#include "SceneLoading.h"
CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(SC_LOGO)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}


void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CSceneLogo;
			break;
		case SC_VILLAGE:
			m_pScene = new CSceneVillage;
			break;
		case SC_STORE:
			m_pScene = new CSceneStore;
			break;
		case SC_HOUSE:
			m_pScene = new CSceneHouse;
			break;
		case SC_FOREST:
			m_pScene = new CSceneForest;
			break;
		case SC_DUNGEON:
			m_pScene = new CSceneDungeon;
			break;
		case SC_BOSS1:
			m_pScene = new CSceneBoss1;
			break;
			//Ãß°¡
		case SC_ENDING:
			m_pScene = new CSceneEnding;
			break;
		case SC_LOAD:
			m_pScene = new CSceneLoading;
			break;

		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}


void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}


void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
