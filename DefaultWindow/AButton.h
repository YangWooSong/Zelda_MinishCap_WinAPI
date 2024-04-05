#pragma once
#include "PlayerUI.h"
class CAButton :
    public CPlayerUI
{
public:
    CAButton();
    CAButton(float _x, float _y);
    virtual ~CAButton();
public:
    void Initialize();
    int Update();
    void Render(HDC hDC);
    void Release();
private:
    ITEM_ID m_eObjId;
    CObj*    m_pWeapon;
    CObj*      m_pPlayer;
};

