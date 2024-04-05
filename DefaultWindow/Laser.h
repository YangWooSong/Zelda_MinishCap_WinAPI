#pragma once
#include "Monster.h"
class CLaser :
    public CMonster
{
public:
    CLaser();
    virtual ~CLaser();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Set_Active(bool _b) { m_bActive = _b; }
private:
    bool    m_bActive;
};

