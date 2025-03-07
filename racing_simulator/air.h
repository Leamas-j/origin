#pragma once

#include "transport.h"

class Air : public Transport
{
public:
    virtual void calcRaceResult() override;
};
