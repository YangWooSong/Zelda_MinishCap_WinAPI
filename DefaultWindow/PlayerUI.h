#pragma once
#include "Obj.h"
class CPlayerUI :
    public CObj
{
public:
    CPlayerUI();
    virtual ~CPlayerUI();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    bool Get_TextActive() { return m_bTextActive; }
    void Set_TextActive(bool _b) { m_bTextActive = _b;}
    int Get_TextNum() { return m_iTextNum; }
    void Plus_TextNum() { m_iTextNum++; }
    void Set_TextNum(int _iNum) { m_iTextNum = _iNum; }
    void Set_KeyUiActive(bool _b) { m_bKeyUiActive = _b; }
    void Set_KeyCount(int _iNum) { m_iKeyCount = _iNum; }
    void Set_GageActive(bool _b) { m_bGageActive = _b; }

    CObj* Get_m_pGageBar() { return m_pGageBar; }
private:
    void Culculate_Rupe();
    void Set_RupeUI();
    void Set_KeyUI();
private:
    CObj*           m_pPlayer;

    int             m_iTextNum;
    int             m_iPlayerRupe_total;
    int             m_iPlayerRupe_0;
    int             m_iPlayerRupe_1;
    int             m_iPlayerRupe_2;
    int             m_iKeyCount;

    bool            m_bTextActive;
    bool            m_bGageActive;
    bool            m_bKeyUiActive;
    VEC2            m_TextSize;
    VEC2            m_TextPos;

    CObj*           m_pAButton;
    CObj*           m_pBButton;
    CObj*           m_pGageBar;
    list<CObj*>     m_UI_HpList;
    list<CObj*>     m_RupeList;
    list<CObj*>     mKeyList;
};

