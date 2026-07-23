#include "AlgoSecondChance.h"
#include "memoryconstants.h"

AlgoSecondChance::AlgoSecondChance(PageTable* pageTable)
    : pageTable(pageTable){
    this->in_queue.resize(MemoryConfig::PAGE_NUM, false);
}

unsigned int AlgoSecondChance::selectPageToEvict() {

    while(true){
        unsigned int victim = this->pages.front();
        PageTableEntry*  entry = this->pageTable->getEntries()[victim];

        if(entry->getFrame_attributes() & MemoryConfig::FRAME_REFERENCED) {

            entry->setFrame_attributes(entry->getFrame_attributes()
                                       & ~MemoryConfig::FRAME_REFERENCED);
            this->pages.pop();
            this->pages.push(victim);
        }else {
            this->pages.pop();
            this->in_queue.at(victim) = false;
            return victim;
        }
    }
}

void AlgoSecondChance::notifyAccess(unsigned int pageIndex) {
    if(!this->in_queue.at(pageIndex)){
        this->in_queue[pageIndex] = true;
        this->pages.push(pageIndex);
    }
}
