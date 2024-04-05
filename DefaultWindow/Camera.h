#pragma once
#include "Define.h"

class CObj;

class CCamera
{
public:CCamera();
	  virtual ~CCamera();

public:
	VEC2 GetLookAtPos() { return m_tLookAtPos; }
	void SetLookAtPos(VEC2 _tLook) { m_tLookAtPos = _tLook; }
	void SetLookAtPos(float _x, float _y) { m_tLookAtPos.x = _x; m_tLookAtPos.y = _y; }

	//타겟 설정
	void SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }

	void SetMaxPos(VEC2 _vPos) { m_vMaxPos = _vPos; }
	void SetMinPos(VEC2 _vPos) { m_vMinPos = _vPos; }


public:
	//렌더될 위치값 계산
	VEC2 GetRenderPos(VEC2 _vObjPos);					//렌더링할 좌표 반환
	VEC2 GetRenderPos(float _x, float _y);

	VEC2 GetWindowPos(VEC2 _vObjPos);					//원래 위치 반환
	VEC2 GetWindowPos(float _x, float _y);


public:
	void Initialize();
	void Update();
	void Render(HDC hDC);

public:
	void CalculateDiff();

private:
	VEC2    m_tLookAtPos;		//바라보는 위치
	CObj* m_pTarget;			//타겟

	VEC2	m_tDiff;			//오브젝트와 카메라 거리 계산용

	VEC2	m_vMaxPos;			//카메라 최대 위치
	VEC2	m_vMinPos;			//카메라 최소 위치

	float	m_fZoom;

public:
	static CCamera* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CCamera;

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
	static CCamera* m_pInstance;

};

