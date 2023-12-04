#pragma once
#include "Object.h"
class Danger :
    public Object
{
public:
    Danger();
    ~Danger();
public:
    void Update() override;

    void Render(HDC _dc) override;
private:
    float m_fDeleteDelay;
    float m_fCurTime;
    bool m_isDie;
};

