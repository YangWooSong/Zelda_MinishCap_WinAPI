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

	//Ÿ�� ����
	void SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }

	void SetMaxPos(VEC2 _vPos) { m_vMaxPos = _vPos; }
	void SetMinPos(VEC2 _vPos) { m_vMinPos = _vPos; }


public:
	//������ ��ġ�� ���
	VEC2 GetRenderPos(VEC2 _vObjPos);					//�������� ��ǥ ��ȯ
	VEC2 GetRenderPos(float _x, float _y);

	VEC2 GetWindowPos(VEC2 _vObjPos);					//���� ��ġ ��ȯ
	VEC2 GetWindowPos(float _x, float _y);


public:
	void Initialize();
	void Update();
	void Render(HDC hDC);

public:
	void CalculateDiff();

private:
	VEC2    m_tLookAtPos;		//�ٶ󺸴� ��ġ
	CObj* m_pTarget;			//Ÿ��

	VEC2	m_tDiff;			//������Ʈ�� ī�޶� �Ÿ� ����

	VEC2	m_vMaxPos;			//ī�޶� �ִ� ��ġ
	VEC2	m_vMinPos;			//ī�޶� �ּ� ��ġ

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

