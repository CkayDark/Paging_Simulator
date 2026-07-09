#include "tlbentry.h"

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

TLBEntry::TLBEntry() {}
