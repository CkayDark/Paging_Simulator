#ifndef TLBENTRY_H
#define TLBENTRY_H

class TLBEntry
{
private:
    unsigned int page_index;
    unsigned int page_frame_index;
    unsigned char frame_attributes;

public:
    TLBEntry();
    unsigned char getFrame_attributes() const;
    unsigned int getPage_frame_index() const;
    unsigned int getPage_index() const;
};

#endif // TLBENTRY_H
