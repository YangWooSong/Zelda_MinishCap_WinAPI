#pragma once
#include "Obj.h"
class CScene;

class CKey :
    public CObj
{
public:
    CKey();
    virtual ~CKey();

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
    int Render_y;
    int Render_x;

    bool    m_bActive;

    CScene* m_pScene;
};

