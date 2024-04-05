#include "stdafx.h"
#include "Slot.h"
#include "BmpMgr.h"

CSlot::CSlot() :m_bSelect(false)
{
}

CSlot::~CSlot()
{
}

void CSlot::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inven/InvenBow.bmp", L"InvenBow");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inven/InvenMage.bmp", L"InvenWand");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inven/InvenShield.bmp", L"InvenShield");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inven/InvenSword.bmp", L"InvenSword");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inven/InvenWindJar.bmp", L"InvenWindJar");
    m_eRender = RENDER_INVEN;
    m_vSize = {78.f, 57.f};
}

int CSlot::Update()
{
    return 0;
}

void CSlot::Late_Update()
{
 
}

void CSlot::Render(HDC hDC)
{
    int Render_x = 0;
    int Render_y = 0;

    switch (m_eItemId)
    {
    case ITEM_SWORD:
        m_pFrameKey = L"InvenSword";
        break;
    case ITEM_BOW:
        m_pFrameKey = L"InvenBow";
        break;
    case ITEM_SHIELD:
        m_pFrameKey = L"InvenShield";
        break;
    case ITEM_WAND:
        m_pFrameKey = L"InvenWand";
        break;
    case ITEM_POT:
        m_pFrameKey = L"InvenWindJar";
        break;
    default:
        break;
    }

    if (m_bSelect)
        Render_x += 78.f;
    else
        Render_x = 0;

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    BitBlt(hDC, m_vPos.x - m_vSize.x*0.5f , m_vPos.y - m_vSize.y * 0.5f, 78, 57, hMemDC, Render_x, Render_y, SRCCOPY);

}

void CSlot::Release()
{
}
