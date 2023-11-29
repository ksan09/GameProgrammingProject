#pragma once
#include "Object.h"
class Texture;
class Gate :
    public Object
{
public:
    Gate();
    ~Gate();
public:
    void Update() override;
    virtual void EnterCollision(Collider* _pOther) override;

    void Render(HDC _dc) override;
public:
    void SetGateScene(wstring name) { m_sceneName = name; }
private:
    bool m_isLoadScene;
    Texture* m_pTex;
    wstring m_sceneName;

};

