#pragma once
#include "Obj.h"

class CScene;

class CKeyRock :
    public CObj
{
public:
    CKeyRock();
    virtual ~CKeyRock();

public:

    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;



public:
    void Set_Active(bool _b) { m_bActive = _b; }
    void OnCollisionEnter(CObj* _pOther);

    void Set_Scene(CScene* _target) { m_pScene = _target; }
private:
    bool    m_bActive;
    CScene* m_pScene;
};

