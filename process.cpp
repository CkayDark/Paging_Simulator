#include "process.h"

Process::Process() {

    this->page_table = new PageTable();
}



PageTable *Process::getPage_table() const {
    return page_table;
}


