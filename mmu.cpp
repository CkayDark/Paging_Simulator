#include "mmu.h"

MMU::MMU(SystemClock* c) : clock(c) {
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

            this->translate(22);

            unsigned int page_frame_index = entry->getPage_frame_index();
            return (page_frame_index << 10) | offset;
        }
    }






















    PageTableEntry* entry = pt->getEntries()[page_index];

    entry->setFrame_attributes(entry->getFrame_attributes() | MemoryConfig::FRAME_TLB_FLAG);
    entry->setFrame_attributes(entry->getFrame_attributes() | MemoryConfig::FRAME_REFERENCED);

    unsigned int page_frame_index = entry->getPage_frame_index();
    return page_frame_index << 10 | offset;
}
