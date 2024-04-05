#pragma once

#include "Obj.h"
#include "Define.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void		Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	
	void		Update();		
	void		Late_Update();
	void		Render(HDC hDC);		
	void		Release();
	void		Delete_ID(OBJID eID);

	list<CObj*>* Get_ObjList(OBJID eID) { return &m_ObjList[eID]; }
	list<CObj*>* Get_ObjList() { return m_ObjList; }

	CObj* Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj* Get_Inven() { return m_ObjList[OBJ_INVEN].front(); };
	CObj* Get_UI() { return m_ObjList[OBJ_UI].front(); };
	CObj* Get_ItemCollider() { return m_ObjList[OBJ_ITEMCOLLIDER].front(); }

	CObj* Get_Target(OBJID eID, CObj* pObj);


private:
	static CObjMgr*		m_pInstance;

	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*>	m_RenderList[RENDER_END + 1];
};

