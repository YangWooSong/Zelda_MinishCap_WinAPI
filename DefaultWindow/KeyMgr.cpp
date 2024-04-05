#include "stdafx.h"
#include "KeyMgr.h"
#include	"MainGame.h"
CKeyMgr* CKeyMgr::m_pInstance = nullptr;

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'R',
	'A',
	'B',
	'T',
	'E',
	'H',
	'I',
	'Y',
	'N',
	'Z',
	VK_SPACE,
	VK_CONTROL,
	VK_RETURN,
	VK_ESCAPE
};

CKeyMgr::CKeyMgr()
{
	Init();			//���Ⱑ �³�
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		//Ű�� �����ִ�.
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{
			if (m_vecKey[i].bPrevPush)
			{
				//�������� ����
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::TAP;
			}
			m_vecKey[i].bPrevPush = true;
		}
		else//Ű�� �ȴ���
		{
			if (m_vecKey[i].bPrevPush)
			{
				//������ ����
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else
			{
				//�������� �ȴ���
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
			m_vecKey[i].bPrevPush = false;
		}
	
	}
}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false});

	}

	
}
