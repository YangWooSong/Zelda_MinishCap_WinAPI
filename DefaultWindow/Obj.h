#pragma once

#include "Define.h"

class CMyBmp;
class CCamera;

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:

	VEC2            Get_Pos() { return m_vPos; }
	void            Set_Pos(float _x, float _y) { m_vPos.x = _x; m_vPos.y = _y; }
	void			Set_PosY(float _y){ m_vPos.y = _y; }
	void			Set_PosX(float _x) { m_vPos.x = _x; }

	VEC2            Get_CameraPos() { return m_vCameraPos; }

	VEC2            Get_Size() { return m_vSize; }
	void            Set_Size(float _x, float _y) { m_vSize.x = _x; m_vSize.y = _y; }
	bool            Get_Dead() { return m_bDead; }
	void            Set_Dead() { m_bDead = true; }

	void            Set_MapBmp(CMyBmp* _bmp) { m_pMapBmp = _bmp; }
	void            Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	bool            Get_IsActive() { return m_bIsActive; }
	void            Set_IsActive(bool bIsActive) { m_bIsActive = bIsActive; }

	void            Set_LookDir(VEC2 vDir) { m_vLookDir = vDir; }
	void			Set_CurState(STATE _eState)		
					{
						m_ePreState = m_eCurState;
						m_eCurState = _eState;
					}
	void			RenderCollision(HDC hDC);

	RECT			Get_Collider() { return m_tCollider; }
	VEC2            Get_Collider_Pos() { return m_vColliderPos; }
	VEC2            Get_Collider_Scale() { return m_vColliderScale; }
	VEC2            Get_Dir() { return m_vLookDir; }
	OBJID            Get_Id() { return m_eId; }

	unordered_set<CObj*>* GetCollisionSet() { return &m_pCollisionOthers; }

public:
	virtual   void      Initialize()   PURE;
	virtual   int       Update()      PURE;
	virtual   void      Late_Update()   PURE;
	virtual   void      Render(HDC hDC) PURE;
	virtual   void      Release()      PURE;

	virtual   void      OnCollisionEnter(CObj* _pOther) {};
	virtual   void      OnCollisionStay(CObj* _pOther) {}
	virtual   void      OnCollisionExit(CObj* _pOther) {};

public:

	void           Set_Collider(float _fx, float _fy, float _fCX, float _fCY);
	void            Move_Frame();
	RENDERID		Get_GroupID() const { return m_eRender; }
	friend            CCamera;
	void			Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void			Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void			Set_Hp(int _iHp) { m_iHp += _iHp; }
	STATE			Get_CurState() { return m_eCurState; }
protected:

	RECT            m_tCollider;
	VEC2			m_vColliderPos;
	VEC2			m_vColliderScale;

	VEC2            m_vPos;
	VEC2            m_vSize;
	//VEC2            m_vNextPos;
	VEC2            m_vLookDir;     //플레이어가 바라보는 방향 벡터

	VEC2            m_vCameraPos;

	//vector<VEC2*>      m_vAniSize;

	CMyBmp* m_pMapBmp;
	CMyBmp* m_pAniBmp;
	CMyBmp* m_pEffectBmp;
	FRAME            m_tFrame;
	bool            m_bDead;

	OBJID            m_eId;
	const TCHAR* m_pFrameKey = L"";

	unordered_set<CObj*> m_pCollisionOthers;

	bool            m_bIsActive;
	float			m_fSpeed;
	float			m_fAngle;

	int				m_iHp;

	RENDERID		m_eRender;
	STATE				m_ePreState;
	STATE				m_eCurState;
	CObj*			m_pTarget;

};

