#pragma once
#include "Object.h"
class Texture;
class HitEffect :
    public Object
{
public:
    HitEffect();
    ~HitEffect();
public:
    void Update() override;
    void Render(HDC _dc) override;
private:
    Texture* m_pTex;
    bool m_isDie;
    float m_fDeleteTime;
    float m_fCurTime;
};

