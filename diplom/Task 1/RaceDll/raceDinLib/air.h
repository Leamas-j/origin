#pragma once

#include "transport.h"

class EXP Air : public Transport
{
public:
    void calcRaceResult() override;
};
