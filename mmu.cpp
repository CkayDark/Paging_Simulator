#include "mmu.h"

MMU::MMU(SystemClock* c) : clock(c) {
    this->next_tlb_victim = 0;
}

unsigned int MMU::translate(unsigned int virtual_address) {

    PageTable* pt = this->process->getPage_table();

    unsigned int page_index = virtual_address >> 10;
    unsigned int offset = virtual_address & (MemoryConfig::PAGE_SIZE - 1);



    for (int i = 0; i < this->tlb->getSize(); i++) {

        if (page_index == this->tlb->getEntries()[i]->getPage_index()
            && this->tlb->getEntries()[i]->getFrame_attributes()
                   & MemoryConfig::FRAME_TLB_FLAG) {

            PageTableEntry* entry =
                this->process->getPage_table()->getEntries()[page_index];

            entry->setFrame_attributes(entry->getFrame_attributes()
                                       | MemoryConfig::FRAME_REFERENCED);

            this->clock->addTime(Latency::TLB_HIT);

            unsigned int page_frame_index = entry->getPage_frame_index();
            return (page_frame_index << 10) | offset;
        }
    }

    this->clock->addTime(Latency::TLB_MISS);

    if(pt->getEntries()[page_index]->getFrame_attributes()
          & MemoryConfig::FRAME_PRESENT){

        PageTableEntry* ptEntry = pt->getEntries()[page_index];
        ptEntry->setFrame_attributes(ptEntry->getFrame_attributes()
                                     | MemoryConfig::FRAME_REFERENCED);


        TLBEntry* tlbEntry = this->tlb->getEntries()[this->findTlbReplacementIndex()];
        tlbEntry->setPage_index(page_index);
        tlbEntry->setPage_frame_index(ptEntry->getPage_frame_index());
        tlbEntry->setFrame_attributes(ptEntry->getFrame_attributes()
                                      | MemoryConfig::FRAME_TLB_FLAG);


        unsigned int page_frame_index = tlbEntry->getPage_frame_index();
        return (page_frame_index << 10) | offset;
    }




}

int MMU::findTlbReplacementIndex() {

    unsigned int victim_index = this->next_tlb_victim;

    this->next_tlb_victim = (this->next_tlb_victim + 1)
                            % this->tlb->getSize();

    return victim_index;
}













