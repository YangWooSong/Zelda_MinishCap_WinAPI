#pragma once
#include "Monster.h"
class CDungeonMonster :
    public CMonster
{

public:
    CDungeonMonster();
    virtual ~CDungeonMonster();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    vector<VEC2> DestinationList;
    int     m_iDestinationIndex;
};

