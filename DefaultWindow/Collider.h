#include "Define.h"

class CObj;

class CCollider
{
public:
	CCollider();
	~CCollider();

public:
	void Set_Owner(CObj* _pOwner) { m_pOwner = _pOwner; }
	void Late_Update();
	void SetOffsetPos(float _fX, float _fY) { m_vOffsetPos = { _fX ,_fY }; }
	void SetScale(float _fX, float _fY) { m_vScale = { _fX ,_fY }; }

	VEC2	GetOfffset() { return m_vOffsetPos; }
	VEC2	GetScale() { return m_vScale; }
	
	void Render(HDC _hDC);

private:
	CObj* m_pOwner;			//collider주인
	VEC2  m_vOffsetPos;		//기준과의 거리 (오브젝트 중심점과의 거리)
	VEC2  m_vFinalPos;		//collider의 위치
	VEC2  m_vScale;			//크기
	friend class CObj;
};