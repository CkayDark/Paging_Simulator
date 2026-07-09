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
    void setFrame_attributes(unsigned char frame_attributes);
    void setPage_frame_index(unsigned int pf_index);
    void setPage_index(unsigned int p_index);
};

#endif // TLBENTRY_H
