#pragma once
#include "Obj.h"
class CDungeonDoor :
    public CObj
{
public:
    CDungeonDoor();
    virtual ~CDungeonDoor();
public:
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;
    void OnCollisionEnter(CObj* _pOther);
public:
    void Set_Active(bool _b) { m_bActive = _b; }
private:
    bool    m_bActive;
};

