#pragma once

#include "kijin_export.h"

struct pimpl;

KIJIN_API class window
{
public:
    window();
    ~window();

private:
    pimpl *Pimpl;
};
