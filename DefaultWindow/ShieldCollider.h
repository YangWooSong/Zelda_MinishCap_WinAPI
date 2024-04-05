#pragma once
#include "Monster.h"
class CShieldCollider :
    public CMonster
{
public:
    CShieldCollider();
    virtual ~CShieldCollider();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Set_Offset(float _x, float _y)
    {
        m_vOffset.x = _x;
        m_vOffset.y = _y;
    }
    void Set_Active(bool _b) { m_bActive = _b; }
private:
    bool    m_bSound;
    bool    m_bActive;
    VEC2    m_vOffset;
};

