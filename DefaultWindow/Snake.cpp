#include "stdafx.h"
#include "Snake.h"
#include <ctime>
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "Camera.h"
CSnake::CSnake() : m_iDir(0), m_iMoveDir(1), m_bIsMove(true)
{
}

CSnake::~CSnake()
{
	Release();
}

void CSnake::Initialize()
{
	m_fSpeed = 0.3f;

	m_eCurState = IDLE;
	m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
	m_pFrameKey = L"Snake";
	m_vSize = { 100.f,100.f };
	
	Set_Collider(0, 0, 0, 0);
	m_eRender = RENDER_GAMEOBJECT;
	m_vLookDir = { 1.f, 0.f };
	m_iHp = 1;
}

int CSnake::Update()
{
	//�ʱ� ��ġ ����
	if(m_InitPos.x == 0 && m_InitPos.y == 0)
		m_InitPos = m_vPos;

	//���� ��
	if (m_iHp <= 0)
	{
		m_eCurState = DEAD;
		m_bIsMove = false;
	}
	if (m_tFrame.bIsPlayDone && m_bDead)
	{
		return OBJ_DEAD;
	}

	if(m_bIsMove)
	{
		//���� �̵�
		if (m_iDir == 1)
		{
			if (m_vPos.x < m_InitPos.x - 30.f || m_vPos.x > m_InitPos.x + 30.f)
			{

				m_vLookDir.x *= -1;
			}
			m_vPos.x += m_vLookDir.x * m_fSpeed;
		}
		else if (m_iDir == -1)//���� �̵�
		{
			if (m_vPos.y < m_InitPos.y - 30.f || m_vPos.y > m_InitPos.y + 30.f)
				m_iMoveDir *= -1;

			m_vPos.y += m_iMoveDir * m_fSpeed;
		}
	}
    return 0;
}

void CSnake::Late_Update()
{
	Set_Collider(m_vPos.x, m_vPos.y, 60, 60);

	Motion_Change();

	if(m_eCurState != DEAD)
	{
		if (m_vLookDir.x == 1)		//������
		{
			m_tFrame.iMotion = 1;
		}
		else if (m_vLookDir.x == -1)	//����
		{
			m_tFrame.iMotion = 2;
		}
	}

	if (m_eCurState == DEAD)
	{
		m_bDead = true;
	}
	
	__super::Move_Frame();
}

void CSnake::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
		(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
		(int)m_vSize.x,			 // ���� ���� ���� ����
		(int)m_vSize.y,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)(m_tFrame.iFrameStart * m_vSize.x),						// ����� ��Ʈ���� ���� x��ǥ
		(int)(m_tFrame.iMotion * m_vSize.y),						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_vSize.x,			// ����� ��Ʈ���� ���� ������
		(int)m_vSize.y,			// ����� ��Ʈ���� ���� ������
		RGB(128, 128, 128));	// ������ �ȼ��� ���� ��

	//RenderCollision(hDC);
}

void CSnake::Release()
{
}

void CSnake::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case WALK:
			if (m_vLookDir.x == 1)		//������
			{
				m_tFrame.iMotion = 1;
			}
			else if (m_vLookDir.x == -1)	//����
			{
				m_tFrame.iMotion = 2;
			}
			else if (m_vLookDir.y == 1) //�Ʒ�
			{
				m_tFrame.iMotion = 0;
			}
			else if (m_vLookDir.y == -1) //��
			{
				m_tFrame.iMotion = 3;
			}
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.dwSpeed = 200.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;
		case IDLE:
			if (m_vLookDir.x == 1)		//������
			{
				m_tFrame.iMotion = 1;
			}
			else if (m_vLookDir.x == -1)	//����
			{
				m_tFrame.iMotion = 2;
			}
			else if (m_vLookDir.y == 1) //�Ʒ�
			{
				m_tFrame.iMotion = 0;
			}
			else if (m_vLookDir.y == -1) //��
			{
				m_tFrame.iMotion = 3;
			}
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.dwSpeed = 200.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;
		case DEAD:
			CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"MC_Enemy_Hit.wav", SOUND_MONSTER, 1.f);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;

			break;

		}

		m_ePreState = m_eCurState;
	}
}
