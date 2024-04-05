#pragma once
#include "Obj.h"
class CDoor :
    public CObj
{
  public:
             CDoor();
   virtual  ~CDoor();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual   void      OnCollisionEnter(CObj* _pOther);


public:
    void Set_Id(ITEM_ID _id) { m_eId = _id; }
    void Set_SceneChange(bool* _b) { m_pSceneChagne = _b; }
private:
    ITEM_ID   m_eId;
    bool*    m_pSceneChagne;
};

