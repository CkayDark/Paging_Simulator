#ifndef TLB_H
#define TLB_H
#include "tlbentry.h"

class TLB
{
private:
    TLBEntry** entries;
    unsigned int size;

public:
    TLB();
    unsigned int getSize() const;
    TLBEntry **getEntries() const;
};

#endif // TLB_H
