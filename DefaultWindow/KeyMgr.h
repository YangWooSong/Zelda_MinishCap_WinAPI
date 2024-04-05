#pragma once

#include "Define.h"


enum class KEY_STATE
{
	NONE,			//������ ���ݵ� �ȴ���
	TAP,			//�� ����
	HOLD,			//������ �ִ�
	AWAY			//�� ��
	
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
	bool bPrevPush;			//���� �����ӿ� ��������
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

