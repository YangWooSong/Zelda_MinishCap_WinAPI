#pragma once
#include "Npc.h"
class CPlayerUI;

class CNpcGrandfather :
    public CNpc
{
public:
    CNpcGrandfather();
    virtual ~CNpcGrandfather();
public:
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Motion_Change();
private:
    DWORD  m_time;
    CPlayerUI* m_pPlayerUi;
};

