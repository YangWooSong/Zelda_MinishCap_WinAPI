#pragma once
#include "Monster.h"
class CLaserBall :
    public CMonster
{
public:
    CLaserBall();
    virtual ~CLaserBall();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Set_ShieldActive(bool _b) { m_bShieldActive = _b; }
    bool Get_ShieldActive() { return m_bShieldActive; }
private:
    void Motion_Change();
    void    Attack();
private:
    float		m_fDistance;
    bool        m_bShieldActive;
    DWORD				m_dwTime;

    CObj*       m_pShield;
    CObj*       m_pLaser;
};

