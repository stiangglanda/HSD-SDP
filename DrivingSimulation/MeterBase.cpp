#include "MeterBase.h"

MeterBase::MeterBase(const ISpeed& speed, DisplayClient::SPtr display) :
    mDisplay{display},
    mSpeed{speed}
{
    if(mDisplay == nullptr)
    {
        throw std::runtime_error("Error in MeterBase: cannot handle nullptr display.");
    }
}