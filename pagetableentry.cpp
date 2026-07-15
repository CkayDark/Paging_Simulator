#include "pagetableentry.h"

PageTableEntry::PageTableEntry() {
    this->frame_attributes = 0;
    this->page_frame_index = 0;
}


unsigned char PageTableEntry::getFrame_attributes() const
{
    return frame_attributes;
}

unsigned int PageTableEntry::getPage_frame_index() const
{
    return page_frame_index;
}

void PageTableEntry::setPage_frame_index(unsigned int newPage_frame_index)
{
    page_frame_index = newPage_frame_index;
}

void PageTableEntry::setFrame_attributes(unsigned char newFrame_attributes)
{
    frame_attributes = newFrame_attributes;
}


