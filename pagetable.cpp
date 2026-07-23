#include "pagetable.h"
#include "memoryconstants.h"

PageTableEntry **PageTable::getEntries() const {
    return entries;
}

unsigned int PageTable::getSize() const
{
    return size;
}

PageTable::PageTable() {

    this->size = MemoryConfig::PAGE_NUM;
    this->entries = new PageTableEntry*[MemoryConfig::PAGE_NUM];

    for(int i=0; i<MemoryConfig::PAGE_NUM; i++){
        this->entries[i] = new PageTableEntry();
        this->entries[i]->setFrame_attributes(0);
        this->entries[i]->setPage_frame_index(0);
    }
}
