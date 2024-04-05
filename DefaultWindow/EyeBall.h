#pragma once
#include "Monster.h"
class CEyeBall :
    public CMonster
{
public:
    CEyeBall();
    virtual ~CEyeBall();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void Motion_Change();
private:
    float		m_fDistance;
};

