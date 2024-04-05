#pragma once
#include "Obj.h"

class CInven :
    public CObj
{

public:
    CInven();
    virtual ~CInven();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    bool    Get_InvenActive() {return m_bInvenActive;}
    void    Set_InvenActive() { m_bInvenActive = !m_bInvenActive; }
    void    Set_SlotActive(ITEM_ID _id);
    ITEM_ID Get_AItem() { return m_eCurAItem; }
    ITEM_ID Get_BItem() { return m_eCurBItem; }
private:
    void		Key_Input();
    ITEM_ID        Select_AItem();
    ITEM_ID        Select_BItem();

private:
    bool    m_bInvenActive;
    ITEM_ID				m_ePreAItem;
    ITEM_ID				m_ePreBItem;
    ITEM_ID				m_eCurAItem;
    ITEM_ID				m_eCurBItem;

    vector<CObj*>     m_vSlotList;
    CObj*             m_pInvenCursor;
};


