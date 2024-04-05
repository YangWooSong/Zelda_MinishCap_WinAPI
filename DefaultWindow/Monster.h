#pragma once
#include "Obj.h"
class CMonster :
    public CObj
{
public:
    CMonster();
    virtual ~CMonster();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void        OnCollisionEnter(CObj* _pOther);
    void		Set_Hit(bool _b) { m_bHit = _b; }

protected:
    bool    m_bHit;
    
};

