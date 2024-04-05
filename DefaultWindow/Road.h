#pragma once
#include "Obj.h"
class CRoad :
    public CObj
{
public:
    CRoad();
    virtual ~CRoad();
public:
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

public:
    void Set_Active(bool _b) { m_bActive = _b; }
    bool Get_Active() { return m_bActive; }
private:
    bool    m_bActive;
};

