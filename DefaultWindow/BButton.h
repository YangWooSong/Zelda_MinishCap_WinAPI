#pragma once
#include "PlayerUI.h"
class CBButton :
    public CPlayerUI
{
public:
    CBButton();
    CBButton(float _x, float _y);
    virtual ~CBButton();
public:
    void Initialize();
    int Update();
    void Render(HDC hDC);
    void Release();
private:
    ITEM_ID m_eObjId;
    CObj* m_pWeapon;
    CObj* m_pPlayer;
};
