#include "mmu.h"

MMU::MMU(SystemClock* c , RAM* ram, IPagingAlgorithm* algo) : clock(c), ram(ram) , algo(algo){
    this->next_tlb_victim = 0;
    this->tlb = new TLB();
}

unsigned int MMU::translate(unsigned int virtual_address) {

    PageTable* pt = this->process->getPage_table();

    unsigned int page_index = virtual_address >> 10;
    unsigned int offset = virtual_address & (MemoryConfig::PAGE_SIZE - 1);


    //1. TLB Lookup
    int frame_index = this->checkTLB(page_index);
    if(frame_index != -1){
        this->clock->addTime(Latency::TLB_HIT);
        pt->getEntries()[page_index]->setFrame_attributes(
            pt->getEntries()[page_index]->getFrame_attributes()
            | MemoryConfig::FRAME_REFERENCED);
        this->algo->notifyAccess(page_index);
        return (frame_index << 10) | offset;
    }



    if(frame_index != -1){
        this->clock->addTime(Latency::TLB_HIT);
        pt->getEntries()[page_index]->setFrame_attributes(
            pt->getEntries()[page_index]->getFrame_attributes() | MemoryConfig::FRAME_REFERENCED
            );
        this->algo->notifyAccess(page_index);
        return (frame_index << 10) | offset;
    }



    this->clock->addTime(Latency::TLB_MISS);
    PageTableEntry* ptEntry = pt->getEntries()[page_index];



    //2. Page Table Hit (Bereits im RAM)
    if(ptEntry->getFrame_attributes() & MemoryConfig::FRAME_PRESENT){
        ptEntry->setFrame_attributes(ptEntry->getFrame_attributes()
                                     | MemoryConfig::FRAME_REFERENCED);
        this->updateTLB(page_index, ptEntry->getPage_frame_index(), ptEntry->getFrame_attributes());
        this->algo->notifyAccess(page_index);
        return (ptEntry->getPage_frame_index() << 10) | offset;
    }


    //3. Page Fault (Nicht im RAM)
    this->clock->addTime(Latency::PAGE_FAULT);


    int freeFrameIndex = this->ram->findFreeFrame();
    //RAM frei?
    if(freeFrameIndex != -1){

        ptEntry->setPage_frame_index(freeFrameIndex);
        this->ram->mapFrame(freeFrameIndex, page_index);

        ptEntry->setFrame_attributes(ptEntry->getFrame_attributes()
                                     | MemoryConfig::FRAME_PRESENT
                                     | MemoryConfig::FRAME_REFERENCED);

        this->updateTLB(page_index, freeFrameIndex, ptEntry->getFrame_attributes());
        this->algo->notifyAccess(page_index);
        return (freeFrameIndex << 10) | offset;
    //RAM voll
    }else {
        unsigned int victimPage = this->algo->selectPageToEvict();
        unsigned int victimFrame = pt->getEntries()[victimPage]->getPage_frame_index();

        //victim Frame freigeben
        PageTableEntry* victimEntry = pt->getEntries()[victimPage];
        victimEntry->setFrame_attributes(victimEntry->getFrame_attributes()
                                         & ~MemoryConfig::FRAME_PRESENT
                                         & ~MemoryConfig::FRAME_REFERENCED);
        this->ram->freeFrame(victimFrame);
        //Verdrängte Page aus TLB löschen
        this->invalidateTLB(victimPage);

        ptEntry->setPage_frame_index(victimFrame);
        this->ram->mapFrame(victimFrame, page_index);

        ptEntry->setFrame_attributes(ptEntry->getFrame_attributes()
                                     | MemoryConfig::FRAME_PRESENT
                                     | MemoryConfig::FRAME_REFERENCED);

        this->updateTLB(page_index, victimFrame, ptEntry->getFrame_attributes());
        this->algo->notifyAccess(page_index);
        return (victimFrame << 10) | offset;

    }
    return -1;
}


int MMU::findTlbReplacementIndex() {

    unsigned int victim_index = this->next_tlb_victim;

    this->next_tlb_victim = (this->next_tlb_victim + 1) % this->tlb->getSize();
    return victim_index;
}

unsigned int MMU::getLastPageIndex() const {
    return this->pageIndex;
}



int MMU::checkTLB(unsigned int page_index) {

    for(int i = 0; i < this->tlb->getSize(); i++){
        TLBEntry* tlbEntry =this->tlb->getEntries()[i];
        if(page_index == tlbEntry->getPage_index()
            && (tlbEntry->getFrame_attributes() & MemoryConfig::FRAME_TLB_FLAG)){
            return tlbEntry->getPage_frame_index();
        }
    }
    return -1;

}


void MMU::updateTLB(unsigned int page_index, unsigned int frame_index, unsigned int attributes) {

    TLBEntry* tlbEntry = this->tlb->getEntries()[this->findTlbReplacementIndex()];
    tlbEntry->setPage_index(page_index);
    tlbEntry->setPage_frame_index(frame_index);
    tlbEntry->setFrame_attributes(attributes | MemoryConfig::FRAME_TLB_FLAG);

}

void MMU::invalidateTLB(unsigned int page_index) {

    for(int i = 0; i < this->tlb->getSize(); i++){
        TLBEntry* entry = this->tlb->getEntries()[i];
        //Falls verdrängte Seite im TLB, mache ungültig
        if(entry->getPage_index() == page_index){
            entry->setFrame_attributes(entry->getFrame_attributes()
                                       & ~MemoryConfig::FRAME_TLB_FLAG);
        }
    }
}













