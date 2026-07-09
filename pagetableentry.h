#ifndef PAGETABLEENTRY_H
#define PAGETABLEENTRY_H

class PageTableEntry
{

private:
    unsigned int page_frame_index;
    unsigned char frame_attributes;

public:
    PageTableEntry();
    unsigned char getFrame_attributes() const;
    unsigned int getPage_frame_index() const;
    void setPage_frame_index(unsigned int newPage_frame_index);
    void setFrame_attributes(unsigned char newFrame_attributes);
};

#endif // PAGETABLEENTRY_H
