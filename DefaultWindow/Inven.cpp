#include "stdafx.h"
#include "Inven.h"
#include "BmpMgr.h"
#include "Slot.h"
#include "AbstractFactory.h"
#include "InvenCursor.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CInven::CInven() : m_bInvenActive(false), m_ePreAItem(ITEM_END), m_ePreBItem(ITEM_END), m_eCurAItem(ITEM_END), m_eCurBItem(ITEM_END)
{
}

CInven::~CInven()
{
    Release();
}

void CInven::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inven/Inven_BackGround.bmp", L"Inven_BackGround");
    m_eRender = RENDER_INVEN;

    //슬롯 생성 및 초기화
    m_vSlotList.push_back(CAbstractFactory<CSlot>::Create(200.f, 128.f , false, ITEM_SWORD));
    m_vSlotList.push_back(CAbstractFactory<CSlot>::Create(310.f, 128.f, false, ITEM_POT));
    m_vSlotList.push_back(CAbstractFactory<CSlot>::Create(420.f, 128.f, false, ITEM_WAND));
    m_vSlotList.push_back(CAbstractFactory<CSlot>::Create(520.f, 128.f, false, ITEM_BOW));
    m_vSlotList.push_back(CAbstractFactory<CSlot>::Create(200.f, 200.f, false, ITEM_SHIELD));

    //커서 생성
    m_pInvenCursor = new CInvenCursor;
    m_pInvenCursor->Initialize();
}

int CInven::Update()
{
    //인벤 창 열릴때만 작동
    if (m_bInvenActive)
        Key_Input();

    return 0;
}

void CInven::Late_Update()
{
}

void CInven::Render(HDC hDC)
{
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Inven_BackGround");
    if (m_bInvenActive)
    {
        BitBlt(hDC, 0.f, 0.f, 960.f, 640.f, hMemDC, 0, 0, SRCCOPY);
        m_pInvenCursor->Render(hDC);

        //슬롯에 들어갈 아이템수에 따라 수정 필요
        for (int i = 0; i <= 4; ++i)
        {
            //아이템을 얻었으면 슬롯 렌더
            if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemGet())
            {
                m_vSlotList[i]->Render(hDC);
            }
        }
    }
}


void CInven::Set_SlotActive(ITEM_ID _id)
{
    for (int i = 0; i <5; ++i)
    {
        //아이템을 얻었으면 슬롯 렌더 활성화
        if (_id == dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId())
        {
            dynamic_cast<CSlot*>(m_vSlotList[i])->Set_Active(true);
        }
    }
}

void CInven::Key_Input()
{
    if (CKeyMgr::Get_Instance()->GetKeySate(KEY::RIGHT) == KEY_STATE::TAP)
    {
        dynamic_cast<CInvenCursor*>(m_pInvenCursor)->Move_Right();
    }
    else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::LEFT) == KEY_STATE::TAP)
    {
        dynamic_cast<CInvenCursor*>(m_pInvenCursor)->Move_Left();
    }
    else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::UP) == KEY_STATE::TAP)
    {
        dynamic_cast<CInvenCursor*>(m_pInvenCursor)->Move_Up();
    }

    else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::DOWN) == KEY_STATE::TAP)
    {
        dynamic_cast<CInvenCursor*>(m_pInvenCursor)->Move_Down();
    }

    else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::A) == KEY_STATE::TAP)
    {
        m_ePreAItem = m_eCurAItem;
        m_eCurAItem = Select_AItem();
        CSoundMgr::Get_Instance()->StopSound(SOUND_INVEN);
        CSoundMgr::Get_Instance()->PlaySound(L"MC_Menu_Select.wav", SOUND_INVEN, 1.f);

    }
    else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::B) == KEY_STATE::TAP)
    {
        m_ePreBItem = m_eCurBItem;
        m_eCurBItem = Select_BItem();
        CSoundMgr::Get_Instance()->StopSound(SOUND_INVEN);
        CSoundMgr::Get_Instance()->PlaySound(L"MC_Menu_Select.wav", SOUND_INVEN, 1.f);
    }
}

ITEM_ID CInven::Select_AItem()
{
    int iInven_x = m_pInvenCursor->Get_Pos().x;
    int iInven_y = m_pInvenCursor->Get_Pos().y;
    ITEM_ID eId = ITEM_END;
    for (int i = 0; i < 5; ++i)
    {
        if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemGet())
        {
            if (m_vSlotList[i]->Get_Pos().x - 20.f < iInven_x && m_vSlotList[i]->Get_Pos().x + 20.f > iInven_x
                && m_vSlotList[i]->Get_Pos().y - 5.f < iInven_y && m_vSlotList[i]->Get_Pos().y + 5.f > iInven_y)
            {
                if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId() != m_eCurAItem)
                {
                    dynamic_cast<CSlot*>(m_vSlotList[i])->Set_Select(true);
                }
                else
                    dynamic_cast<CSlot*>(m_vSlotList[i])->Set_Select(false);
               
                if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId() != m_ePreAItem && m_ePreAItem != ITEM_END)
                {
                    dynamic_cast<CSlot*>(m_vSlotList[m_ePreAItem])->Set_Select(false);
                }

                if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId() == m_eCurBItem)
                    m_eCurBItem = ITEM_END;

                if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_Select())
                    return dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId();
                else
                    return ITEM_END;
            }
        }
    }

    return eId;
   
}

ITEM_ID CInven::Select_BItem()
{
    int iInven_x = m_pInvenCursor->Get_Pos().x;
    int iInven_y = m_pInvenCursor->Get_Pos().y;
    ITEM_ID eId = ITEM_END;
    for (int i = 0; i < 5; ++i)
    {
        if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemGet())
        {
            if (m_vSlotList[i]->Get_Pos().x - 20.f < iInven_x && m_vSlotList[i]->Get_Pos().x + 20.f > iInven_x
                && m_vSlotList[i]->Get_Pos().y - 5.f < iInven_y && m_vSlotList[i]->Get_Pos().y + 5.f > iInven_y)
            {
                if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId() != m_eCurBItem)
                {
                    dynamic_cast<CSlot*>(m_vSlotList[i])->Set_Select(true);
                }
                else
                    dynamic_cast<CSlot*>(m_vSlotList[i])->Set_Select(false);

                if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId() != m_ePreBItem && m_ePreBItem != ITEM_END)
                {
                    dynamic_cast<CSlot*>(m_vSlotList[m_ePreBItem])->Set_Select(false);
                }
                if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId() == m_eCurAItem)
                    m_eCurAItem = ITEM_END;
                if (dynamic_cast<CSlot*>(m_vSlotList[i])->Get_Select())
                    return dynamic_cast<CSlot*>(m_vSlotList[i])->Get_ItemId();
                else
                    return ITEM_END;
            }
        }
    }
    return eId;

}

void CInven::Release()
{
    Safe_Delete(m_pInvenCursor);
    for (int i = 0; i < m_vSlotList.size(); ++i)
    {
        Safe_Delete(m_vSlotList[i]);
    }
}
