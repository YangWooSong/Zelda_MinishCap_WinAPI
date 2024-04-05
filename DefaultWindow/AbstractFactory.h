#pragma once

#include "Obj.h"
#include "Scene.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}
	//애니메이션 배경 생성
	static CObj* Create(float _fX, float _fY, int _iNum)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		if (dynamic_cast<CMapObject*>(pObj) != nullptr)
		{
			dynamic_cast<CMapObject*>(pObj)->Set_iNum(_iNum);
		}
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, ITEM_ID _id)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		if (dynamic_cast<CStoreBox*>(pObj) != nullptr)
		{
			dynamic_cast<CStoreBox*>(pObj)->Set_Item(_id);
		}
		return pObj;
	}
	//천장 생성
	static CObj* Create(float _fX, float _fY, SCENEID _id, int _iNum)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		dynamic_cast<CCeilling*>(pObj)->Set_SceneID(_id);
		dynamic_cast<CCeilling*>(pObj)->Set_iNum(_iNum);
		return pObj;
	}

	//아이템 생성
	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY, ITEM_ID _id)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		dynamic_cast<CWeapon*>(pObj)->Set_ItemId(_id);
		return pObj;
	}

	//기본 오브젝트 생성
	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);

		return pObj;
	}

	//열쇠, 열쇠 돌, 화로
	static CObj* Create(float _fX, float _fY, CScene* _target)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		if(dynamic_cast<CKey*>(pObj) != nullptr)
		{
			dynamic_cast<CKey*>(pObj)->Set_Scene(_target);
		}
		else if (dynamic_cast<CKeyRock*>(pObj) != nullptr)
		{
			dynamic_cast<CKeyRock*>(pObj)->Set_Scene(_target);
		}
		else if (dynamic_cast<CBrazier*>(pObj) != nullptr)
		{
			dynamic_cast<CBrazier*>(pObj)->Set_Scene(_target);
		}
		else if (dynamic_cast<CSieldMonster*>(pObj) != nullptr)
		{
			dynamic_cast<CSieldMonster*>(pObj)->Set_Scene(_target);
		}
		return pObj;
	}

	//문 생성
	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY, ITEM_ID _id, bool* _pScenechange)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		dynamic_cast<CDoor*>(pObj)->Set_Id(_id);
		dynamic_cast<CDoor*>(pObj)->Set_SceneChange(_pScenechange);
		return pObj;
	}

	//아이템 슬롯 생성
	static CObj* Create(float _fX, float _fY,bool _get, ITEM_ID _id)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		dynamic_cast<CSlot*>(pObj)->Set_ItemId(_id);
		dynamic_cast<CSlot*>(pObj)->Set_Active(_get);
		return pObj;
	}

	//각도 총알 생성, 게이지 바
	static CObj* Create(float _fX, float _fY, float _fAngle, CObj* _target)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_Target(_target);
		return pObj;
	}

	//방향 총알 생성
	static CObj* Create(float _fX, float _fY, VEC2 _vDir, CObj* _target)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_LookDir(_vDir);
		pObj->Set_Target(_target);
		return pObj;
	}
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}
};

