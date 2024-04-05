#include "stdafx.h"
#include "PlayerUI.h"
#include "AButton.h"
#include "BButton.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "UI_HP.h"
#include "Inven.h"
#include "BmpMgr.h"
#include "Number.h"
#include "GageBarBack.h"

CPlayerUI::CPlayerUI() :m_pAButton(nullptr), m_pBButton(nullptr), m_pPlayer(nullptr)
, m_iPlayerRupe_total(0), m_iPlayerRupe_0(0), m_iPlayerRupe_1(0), m_iPlayerRupe_2(0)
, m_iTextNum(0), m_bTextActive(false), m_bKeyUiActive(false), m_bGageActive(false)
{
    m_vPos = { WINCX * 0.5f,WINCY * 0.5f };
}

CPlayerUI::~CPlayerUI()
{
    Release();
}


void CPlayerUI::Initialize()
{
    m_eRender = RENDER_UI;

    m_pAButton = new CAButton(576.f, 45.f);
    m_pAButton->Initialize();

    m_pBButton = new CBButton(636.f, 45.f);
    m_pBButton->Initialize();

    m_pGageBar = new CGageBarBack();
    m_pGageBar->Set_Pos(30.f, 65.f);
    m_pGageBar->Initialize();
    m_pGageBar->Set_IsActive(false); 

    m_TextSize = { 672.f, 144.f };
    m_TextPos = {360.f,380.f};
    m_pFrameKey = L"House_Text_01";
    m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
}

int CPlayerUI::Update()
{
     m_pGageBar->Set_IsActive(m_bGageActive);

    m_pAButton->Update();
    m_pBButton->Update();
    m_pGageBar->Update();

    //전에 담아둔 리스트 내용물 빼내기
    for (auto iter = m_UI_HpList.begin(); iter != m_UI_HpList.end(); )
    {
        Safe_Delete<CObj*>(*iter);
        iter= m_UI_HpList.erase(iter);
    }
    for (auto iter = m_RupeList.begin(); iter != m_RupeList.end(); )
    {
        Safe_Delete<CObj*>(*iter);
        iter = m_RupeList.erase(iter);
    }
    switch (m_iTextNum)
    {
    case 0:
        m_pFrameKey = L"House_Text_01";
        break;
    case 1:
        m_pFrameKey = L"House_Text_02";
        break;
    case 2:
        m_pFrameKey = L"Store_Text_01";
        break;
    default:
        break;
    }

    Culculate_Rupe();
    return 0;
}

void CPlayerUI::Late_Update()
{
    //체력 UI를 매 프레임 다시 그림
    for (int i = 0; i < dynamic_cast<CPlayer*>(m_pPlayer)->Get_DefaultHp()/4; ++i)
    {
        m_UI_HpList.push_back(CAbstractFactory<CUI_HP>::Create(40 + i * 30.f, 40));
        if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_CurHp()/4 > i)
        {
            //하트 채우기
            dynamic_cast<CUI_HP*>(m_UI_HpList.back())->Set_Full(true);
        }
        else
        {
            if(m_UI_HpList.size() == dynamic_cast<CPlayer*>(m_pPlayer)->Get_CurHp() / 4 + 1)
            {
                dynamic_cast<CUI_HP*>(m_UI_HpList.back())->Set_Full(false);
                dynamic_cast<CUI_HP*>(m_UI_HpList.back())->Set_FullCount(dynamic_cast<CPlayer*>(m_pPlayer)->Get_CurHp() % 4);
            }
            else
            {
                dynamic_cast<CUI_HP*>(m_UI_HpList.back())->Set_Full(false);
                dynamic_cast<CUI_HP*>(m_UI_HpList.back())->Set_FullCount(0);
            }

        }
    }


    Set_RupeUI();
    if (m_bKeyUiActive)
        Set_KeyUI();
}





void CPlayerUI::Render(HDC hDC)
{
    m_pAButton->Render(hDC);
    m_pBButton->Render(hDC);
    m_pGageBar->Render(hDC);


    if(!dynamic_cast<CInven*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inven())->Get_InvenActive())
    {
        for (auto& iter : m_UI_HpList)
        {
            iter->Render(hDC);
        }
        for (auto& iter : m_RupeList)
        {
            iter->Render(hDC);
        }
        if (m_bKeyUiActive)
        {
            for (auto& iter : mKeyList)
            {
                iter->Render(hDC);
            }
        }
    }
    if (m_bTextActive)
    {
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

        GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
            (int)(m_TextPos.x - m_TextSize.x * 0.5f), // 복사 받을 위치의 left
            (int)(m_TextPos.y - m_TextSize.y * 0.5f),			 // 복사 받을 위치의 top
            (int)m_TextSize.x,			 // 복사 받을 가로 길이
            (int)m_TextSize.y,			 // 복사 받을 세로 길이
            hMemDC,					// 비트맵을 가지고 있는 dc
            0,						// 출력할 비트맵의 시작 x좌표
            0,						// 출력할 비트맵의 시작 y좌표
            (int)m_TextSize.x,		// 출력할 비트맵의 가로 사이즈
            (int)m_TextSize.y,					// 출력할 비트맵의 세로 사이즈
            RGB(255, 0, 255));	// 제거할 픽셀의 색상 값
    }

}

void CPlayerUI::Release()
{
    Safe_Delete(m_pBButton);
    Safe_Delete(m_pAButton);
    for (auto& iter : m_UI_HpList)
    {
        Safe_Delete<CObj*>(iter);
    }
    for (auto& iter : m_RupeList)
    {
        Safe_Delete<CObj*>(iter);
    }
}

void CPlayerUI::Culculate_Rupe()
{
    m_iPlayerRupe_total = dynamic_cast<CPlayer*>(m_pPlayer)->Get_Rupe();
    //1의 자리 계산
    m_iPlayerRupe_2 = m_iPlayerRupe_total % 10;
    m_iPlayerRupe_total /= 10;
    //10의 자리 계산
    m_iPlayerRupe_1 = m_iPlayerRupe_total % 10;
    m_iPlayerRupe_total /= 10;
    //100의 자리 계산
    m_iPlayerRupe_0 = m_iPlayerRupe_total % 10;
}

void CPlayerUI::Set_RupeUI()
{
    m_RupeList.push_back(CAbstractFactory<CNumber>::Create(570.f, 456.f));
    dynamic_cast<CNumber*>(m_RupeList.back())->Set_Full(10);
    m_RupeList.push_back(CAbstractFactory<CNumber>::Create(600 + 0 * 25.f, 456.f));
    dynamic_cast<CNumber*>(m_RupeList.back())->Set_Full(m_iPlayerRupe_0);
    m_RupeList.push_back(CAbstractFactory<CNumber>::Create(600 + 1* 25.f, 456.f));
    dynamic_cast<CNumber*>(m_RupeList.back())->Set_Full(m_iPlayerRupe_1);
    m_RupeList.push_back(CAbstractFactory<CNumber>::Create(600 + 2 * 25.f, 456.f));
    dynamic_cast<CNumber*>(m_RupeList.back())->Set_Full(m_iPlayerRupe_2);

}

void CPlayerUI::Set_KeyUI()
{
    m_RupeList.push_back(CAbstractFactory<CNumber>::Create(570.f, 420.f));
    dynamic_cast<CNumber*>(m_RupeList.back())->Set_Full(11);
    m_RupeList.push_back(CAbstractFactory<CNumber>::Create(600 + 0 * 25.f, 420.f));
    dynamic_cast<CNumber*>(m_RupeList.back())->Set_Full(0);
    m_RupeList.push_back(CAbstractFactory<CNumber>::Create(600 + 1 * 25.f, 420.f));
    dynamic_cast<CNumber*>(m_RupeList.back())->Set_Full(m_iKeyCount);
  
}
