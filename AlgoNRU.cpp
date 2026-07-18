#include "AlgoNRU.h"

AlgoNRU::AlgoNRU(PageTable* pagetable) : pagetable(pagetable){}

unsigned int AlgoNRU::selectPageToEvict() {

}

void AlgoNRU::notifyAccess(unsigned int pageIndex) {

    ++this->access_count;
    if(this->access_count >= RESET_INTERVAL){
        for(int i=0; i<this->pagetable->getSize(); i++){
            this->pagetable->getEntries()[i]->setFrame_attributes(
                this->pagetable->getEntries()[i]->getFrame_attributes()
                & ~MemoryConfig::FRAME_REFERENCED);
        }
    this->access_count = 0;
    }

}
