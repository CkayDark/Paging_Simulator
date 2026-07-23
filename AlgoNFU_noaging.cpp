#include "AlgoNFU_noaging.h"
#include "memoryconstants.h"

AlgoNFU_noAging::AlgoNFU_noAging(PageTable* pageTable) : pageTable(pageTable){
    this->counterForEachPage.resize(MemoryConfig::PAGE_NUM, 0);
}


unsigned int AlgoNFU_noAging::selectPageToEvict() {
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



void AlgoNFU_noAging::notifyAccess(unsigned int pageIndex) {
    ++this->counterForEachPage.at(pageIndex);
}
