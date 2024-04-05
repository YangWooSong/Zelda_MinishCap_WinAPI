#pragma once
#include "Monster.h"
class CSnake :
    public CMonster
{
public:
    CSnake();
    virtual ~CSnake();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Set_Dirint(int _i) { m_iDir = _i; }
private:
    void Motion_Change();

private:
    bool    m_bIsMove;
    int    m_iDir;
    int   m_iMoveDir;
    VEC2 m_InitPos;
};

