#include "process.h"

PageTable *Process::getPage_table() const
{
    return page_table;
}

Process::Process() {}
