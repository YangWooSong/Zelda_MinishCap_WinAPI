#include "stdafx.h"
#include "PlayerBullet.h"
#include "BmpMgr.h"
#include "Camera.h"

#include "ObjMgr.h"
#include "Monster.h"
#include "LaserBall.h"
#include "Player.h"
CPlayerBullet::CPlayerBullet()
{
}

CPlayerBullet::~CPlayerBullet()
{
    Release();
}

void CPlayerBullet::Initialize()
{
	m_pFrameKey = L"FireBall";
	m_vSize = { 48.f, 48.f };
	m_fSpeed = 5.f;

	m_eCurState = IDLE;

	m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };

	Set_Collider(0, 0, 0, 0);
	m_eRender = RENDER_GAMEOBJECT;

	m_iHp = 1;
	m_fAngle = 0.f;
	m_eId = OBJ_BULLET;
}

int CPlayerBullet::Update()
{
	if (m_iHp <= 0)
	{
		m_eCurState = DEAD;
		return OBJ_DEAD;
	}

	if (m_vLookDir.x == 1)
	{
		m_vPos.x += m_fSpeed;
	}
	else if(m_vLookDir.x == -1)
	{
		m_vPos.x -= m_fSpeed;
	}
	else if (m_vLookDir.y == 1)
	{
		m_vPos.y += m_fSpeed;
	}
	else if (m_vLookDir.y == -1)
	{
		m_vPos.y -= m_fSpeed;
	}
	return OBJ_NOEVENT;
}

void CPlayerBullet::Late_Update()
{
	if (m_ePreState != m_eCurState)
	{

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.bIsPlayDone = true;

		m_ePreState = m_eCurState;

	}
	Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);

	__super::Move_Frame();
}

void CPlayerBullet::Render(HDC hDC)
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
		RGB(0, 0, 255));	// ������ �ȼ��� ���� ��

	//RenderCollision(hDC);
}

void CPlayerBullet::OnCollisionEnter(CObj* _pOther)
{
	m_iHp -= 1;

	float   fX(0.f), fY(0.f);
	/*if (pMonster == nullptr)
		return;*/
	CObj* pObject = _pOther;

	//�浹ü ���� Ȯ��
	if (dynamic_cast<CMonster*>(_pOther) != nullptr)
	{
		//	pObject = dynamic_cast<CMonster*>(_pOther);
	}


	RECT intersect = {};

	if (::IntersectRect(&intersect, &pObject->Get_Collider(), &m_tCollider))
	{
		int w = intersect.right - intersect.left;
		int h = intersect.bottom - intersect.top;

		if (w > h)
		{
			if (intersect.top == m_tCollider.top)
			{
				//������ ������ ���a��
				if (pObject->Get_Id() == OBJ_EYES)
				{
					if (dynamic_cast<CLaserBall*>(pObject)->Get_ShieldActive() == true)
					{
						if (dynamic_cast<CPlayer*>(m_pTarget)->Get_ITEMID() == ITEM_POT)
							dynamic_cast<CLaserBall*>(pObject)->Set_ShieldActive(false);
						else
							return;
					}
					else pObject->Set_Hp(-1);
				}
				else
				{
					pObject->Set_Hp(-1);
					pObject->Set_CurState(HIT);
				}
			}
			else
			{
				//������ ������ ��츸
				if (pObject->Get_Id() == OBJ_EYES)
				{
					if (dynamic_cast<CLaserBall*>(pObject)->Get_ShieldActive() == true)
					{
						if (dynamic_cast<CPlayer*>(m_pTarget)->Get_ITEMID() == ITEM_POT)
							dynamic_cast<CLaserBall*>(pObject)->Set_ShieldActive(false);
						else
							return;
					}
					else pObject->Set_Hp(-1);
				}
				else
				{
					pObject->Set_Hp(-1);
					pObject->Set_CurState(HIT);
				}
			}
		}
		else
		{
			if (intersect.left == m_tCollider.left)
			{
				//������ ������ ��츸
				if (pObject->Get_Id() == OBJ_EYES)
				{
					if (dynamic_cast<CLaserBall*>(pObject)->Get_ShieldActive() == true)
					{
						if (dynamic_cast<CPlayer*>(m_pTarget)->Get_ITEMID() == ITEM_POT)
							dynamic_cast<CLaserBall*>(pObject)->Set_ShieldActive(false);
						else
							return;
					}
					else pObject->Set_Hp(-1);
				}
				else
				{
					pObject->Set_Hp(-1);
					pObject->Set_CurState(HIT);
				}
			}
			else
			{
				//������ ������ ��츸
				if (pObject->Get_Id() == OBJ_EYES)
				{
					if (dynamic_cast<CLaserBall*>(pObject)->Get_ShieldActive() == true)
					{
						if (dynamic_cast<CPlayer*>(m_pTarget)->Get_ITEMID() == ITEM_POT)
							dynamic_cast<CLaserBall*>(pObject)->Set_ShieldActive(false);
						else
							return;
					}
					else pObject->Set_Hp(-1);
				}
				else
				{
					pObject->Set_Hp(-1);
					pObject->Set_CurState(HIT);
				}
			}
		}

	}
}

void CPlayerBullet::Release()
{
}

void CPlayerBullet::Motion_Change()
{
}
