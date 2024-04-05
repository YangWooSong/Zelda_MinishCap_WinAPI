#pragma once
#include "Monster.h"
class CScene;

class CSieldMonster :
    public CMonster
{
public:
    CSieldMonster();
    virtual ~CSieldMonster();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
   public:
    void Set_Dir();
    void Set_Scene(CScene* _target) { m_pScene = _target; }
    void Set_Active(bool _b) { m_bActive = _b; }
    bool Get_Active() { return m_bActive; }
private:
    void Motion_Change();
    void Set_SwordCollider();
    
private:
    bool    m_bChangeState;
    bool    m_bActive;
    CObj* m_pPlayer;
    CObj* m_pShieldCollider;
    CScene* m_pScene;

};

