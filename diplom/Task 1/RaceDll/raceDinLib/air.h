#pragma once

#include "transport.h"

class EXP Air : public Transport
{
public:
    virtual void calcRaceResult() override;
};
