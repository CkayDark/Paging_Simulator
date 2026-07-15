#ifndef PROCESS_H
#define PROCESS_H
#include "pagetable.h"

class Process  {

private:
    unsigned char process_id;
    PageTable* page_table;

public:
    Process();
    PageTable *getPage_table() const;
};

#endif // PROCESS_H
