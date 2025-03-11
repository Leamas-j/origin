#pragma once

#include "transport.h"

class Air : public Transport
{
public:
    void calcRaceResult() override;
};
