#pragma once
#include "Obj.h"
class CEffect :
    public CObj
{
public:
    CEffect();
    virtual ~CEffect();

public:
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

public:
    void Motion_Change();
    void    Set_Active(bool _b) { m_bActive = _b; }
private:
    bool    m_bActive;
    VEC2    m_vOwnerDir;
};

