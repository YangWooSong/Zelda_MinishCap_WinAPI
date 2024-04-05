#pragma once
#include "Obj.h"
class CCeilling :
    public CObj
{
public:
    CCeilling();
    ~CCeilling();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    void Set_SceneID(SCENEID _id) { m_eSceneId = _id; }
    void    Set_iNum(int _iN) { m_iNum = _iN; }
private:
    SCENEID m_eSceneId;
    int     m_iNum;

    int     m_iRenderX;
    int     m_iRenderY;
};

