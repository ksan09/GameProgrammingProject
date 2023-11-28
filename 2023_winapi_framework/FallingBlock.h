#pragma once
#include "Block.h"
class FallingBlock :
    public Block
{
public:
    FallingBlock();
    ~FallingBlock();
public:
    void Update() override;

};

