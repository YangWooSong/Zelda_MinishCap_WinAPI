#pragma once
#include "Obj.h"
class CMovingFloor :
    public CObj
{
public:
    CMovingFloor();
    virtual ~CMovingFloor();
public:
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

    void OnCollisionStay(CObj* _pOther);

private:
    int         m_iDir;
    bool        m_bMove;
    DWORD       m_time;
};

