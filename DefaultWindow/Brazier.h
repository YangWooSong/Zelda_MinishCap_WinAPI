#pragma once
#include "Obj.h"

class CScene;

class CBrazier :
    public CObj
{
public:
    CBrazier();
    virtual ~CBrazier();
public:
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

public:
    void OnCollisionEnter(CObj* _pOther);
    void Set_Scene(CScene* _target) { m_pScene = _target; }
    bool Get_Active() { return m_bActive; }
private:
    bool    m_bActive;
    CScene* m_pScene;
};

