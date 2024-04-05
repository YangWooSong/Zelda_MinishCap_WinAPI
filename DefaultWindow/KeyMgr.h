#pragma once

#include "Define.h"


enum class KEY_STATE
{
	NONE,			//전에도 지금도 안눌린
	TAP,			//막 누른
	HOLD,			//누르고 있는
	AWAY			//막 뗀
	
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	R,
	A,
	B,
	T,
	E,
	H,
	I,
	Y,
	N,
	Z,
	SPACE,
	CTRL,
	ENTER,
	ESC,
	LAST,
};

struct tKeyInfo
{
	KEY_STATE	eState;
	bool bPrevPush;			//이전 프레임에 눌렀는지
};

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;

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


private:
	static CKeyMgr* m_pInstance;

private:
	vector<tKeyInfo> m_vecKey;
public:
	void Init();
	void Update();
	KEY_STATE	GetKeySate(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
};

