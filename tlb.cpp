#include "tlb.h"

unsigned int TLB::getSize() const
{
    return size;
}

TLBEntry **TLB::getEntries() const
{
    return entries;
}

TLB::TLB() {}
