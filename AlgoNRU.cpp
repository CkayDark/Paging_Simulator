#include "AlgoNRU.h"

AlgoNRU::AlgoNRU(PageTable* pagetable) : pagetable(pagetable){}

unsigned int AlgoNRU::selectPageToEvict() {

    // !ref && !mod
    std::vector<unsigned int> class0;
    // !ref && mod
    std::vector<unsigned int> class1;
    // ref && !mod
    std::vector<unsigned int> class2;
    // ref && mod
    std::vector<unsigned int> class3;

    for(int i=0; i<this->pagetable->getSize(); i++){
        PageTableEntry* entry = pagetable->getEntries()[i];
        //im RAM?
        if(entry->getFrame_attributes()
            & MemoryConfig::FRAME_PRESENT){
            bool ref = entry->getFrame_attributes() & MemoryConfig::FRAME_REFERENCED;
            bool mod = entry->getFrame_attributes() & MemoryConfig::FRAME_MODIFIED;

            if(!ref && !mod){
                class0.push_back(i);
            } else if(!ref && mod){
                    class1.push_back(i);
            }else  if(ref && !mod){
                    class2.push_back(i);
            }else class3.push_back(i);

            }

        }

    if(!class0.empty()){
        return class0.at(0);
    }
    if(!class1.empty()){
        return class1.at(0);
    }
    if(!class2.empty()){
        return class2.at(0);
    }
    if(!class3.empty()){
        return class3.at(0);
    }

    return 0;
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
