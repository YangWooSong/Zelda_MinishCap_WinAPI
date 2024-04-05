#include "stdafx.h"
#include "Obj.h"
#include "Collider.h"
#include "Camera.h"
CObj::CObj() : m_fSpeed(0.f),  m_bDead(false), m_pTarget(nullptr), m_fAngle(0)
{
	ZeroMemory(&m_tCollider, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));	
}

CObj::~CObj()
{
	Release();
}

void CObj::Release()
{
	
}

void CObj::RenderCollision(HDC hDC)
{
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	HPEN MyPen, OldPen;
	HBRUSH MyBrush, OldBrush;

	MyPen = CreatePen(PS_DASH, 2, RGB(0, 0,255));
	OldPen = (HPEN)SelectObject(hDC, MyPen);

	MyBrush = CreateSolidBrush(RGB(255,0,255));
	OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);

	SelectObject(hDC, GetStockObject(NULL_BRUSH));

	Rectangle(hDC, 
		(int)m_vCameraPos.x - m_vColliderScale.x * 0.5f,
		(int)m_vCameraPos.y - m_vColliderScale.y * 0.5f,
		(int)m_vCameraPos.x + m_vColliderScale.x * 0.5f,
		(int)m_vCameraPos.y + m_vColliderScale.y * 0.5f
	);
	DeleteObject(SelectObject(hDC,OldPen));
	DeleteObject(SelectObject(hDC, OldBrush));
}


void CObj::Set_Collider(float _fx, float _fy, float _fCX, float _fCY)
{
	m_tCollider.left = long(_fx - (_fCX * 0.5f));
	m_tCollider.top = long(_fy - (_fCY * 0.5f));
	m_tCollider.right = long(_fx + (_fCX * 0.5f));
	m_tCollider.bottom = long(_fy + (_fCY * 0.5f));

	m_vColliderPos.x = _fx;
	m_vColliderPos.y = _fy;

	m_vColliderScale.x = _fCX;
	m_vColliderScale.y = _fCY;
}


void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		//ÃÊ±âÈ­
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.bIsPlayDone = true;
		}
	}

}
