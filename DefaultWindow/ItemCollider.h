#pragma once
#include "Obj.h"
class CItemCollider :
    public CObj
{
public:
    CItemCollider();
    virtual ~CItemCollider();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void OnCollisionEnter(CObj* _pOther);
    void Release() override;

public:
    void Set_Offset(float _x, float _y)
    {
        m_vOffset.x = _x;
        m_vOffset.y= _y;
    }

private:
    VEC2    m_vOffset;
};

