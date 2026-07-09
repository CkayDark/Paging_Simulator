#ifndef PAGETABLE_H
#define PAGETABLE_H
#include "pagetableentry.h"
#include "memoryconstants.h"

class PageTable
{
private:
    PageTableEntry** entries;
    unsigned int size;

public:
    PageTable();
    PageTableEntry **getEntries() const;
    unsigned int getSize() const;
};

#endif // PAGETABLE_H
