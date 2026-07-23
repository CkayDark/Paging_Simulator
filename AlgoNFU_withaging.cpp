#include "AlgoNFU_withaging.h"
#include "memoryconstants.h"

AlgoNFU_withAging::AlgoNFU_withAging(PageTable* pageTable)
    : pageTable(pageTable){
    this->counterForEachPage.resize(MemoryConfig::PAGE_NUM, 0);
}

unsigned int AlgoNFU_withAging::selectPageToEvict() {
    unsigned int rarest_page = 0;
    unsigned int lowest_count = 999999999;

    for(int i=0; i<this->pageTable->getSize(); i++){
        if(!(this->pageTable->getEntries()[i]->getFrame_attributes()
              & MemoryConfig::FRAME_PRESENT)){
            continue;

        }else if(this->counterForEachPage.at(i) < lowest_count){
            lowest_count = counterForEachPage.at(i);
            rarest_page = i;
        }
    }


    return rarest_page;
}

void AlgoNFU_withAging::notifyAccess(unsigned int pageIndex) {

    ++this->access_count;
    if(this->access_count == this->RESET_INTERVAL){
        this->access_count = 0;

        for(int i=0; i<MemoryConfig::PAGE_NUM; i++){

            this->counterForEachPage.at(i) >>= 1;

            if(this->pageTable->getEntries()[i]->getFrame_attributes()
                & MemoryConfig::FRAME_REFERENCED) {
                this->counterForEachPage.at(i) |= 0x80000000;

                this->pageTable->getEntries()[i]->setFrame_attributes(
                    this->pageTable->getEntries()[i]->getFrame_attributes()
                    & ~MemoryConfig::FRAME_REFERENCED);
            }
        }
    }
}
