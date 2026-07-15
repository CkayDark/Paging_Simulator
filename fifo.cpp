#include "fifo.h"
#include "memoryconstants.h"

FIFO::FIFO() {
    this->in_queue.resize(MemoryConfig::PAGE_NUM, false);
}

void FIFO::notifyAccess(unsigned int pageIndex) {
    if(!this->in_queue.at(pageIndex)){
        this->in_queue[pageIndex] = true;
        this->pages.push(pageIndex);
    }
}

unsigned int FIFO::selectPageToEvict() {
    int oldestPage = this->pages.front();
    this->pages.pop();
    this->in_queue[oldestPage] = false;
    return oldestPage;
}
