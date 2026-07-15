#include "tlb.h"

TLB::TLB() {
    this->size = 16;

    this->entries = new TLBEntry*[this->size];

    for(unsigned int i = 0; i < this->size; i++){
        this->entries[i] = new TLBEntry();

        this->entries[i]->setPage_index(0);
        this->entries[i]->setPage_frame_index(0);
        this->entries[i]->setFrame_attributes(0);
    }
}

unsigned int TLB::getSize() const {
    return size;
}

TLBEntry **TLB::getEntries() const {
    return entries;
}


