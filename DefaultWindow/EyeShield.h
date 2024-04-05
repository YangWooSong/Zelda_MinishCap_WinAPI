#pragma once
#include "Monster.h"
class CEyeShield :
    public CMonster
{
public:
    CEyeShield();
    virtual ~CEyeShield();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    bool    Get_Active() { return m_bActive; }
    void    Set_Active(bool _b) { m_bActive = _b; }
private:
    bool    m_bActive;
};

