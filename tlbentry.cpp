#include "tlbentry.h"

TLBEntry::TLBEntry() {}


unsigned char TLBEntry::getFrame_attributes() const
{
    return frame_attributes;
}

unsigned int TLBEntry::getPage_frame_index() const
{
    return page_frame_index;
}

unsigned int TLBEntry::getPage_index() const
{
    return page_index;
}

void TLBEntry::setFrame_attributes(unsigned char frame_attributes)  {
    this->frame_attributes = frame_attributes;
}

void TLBEntry::setPage_frame_index(unsigned int pf_index) {
    this->page_frame_index = pf_index;
}

void TLBEntry::setPage_index(unsigned int p_index) {
    this->page_index = p_index;
}


