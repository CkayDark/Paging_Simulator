#include "AlgoLRU.h"

AlgoLRU::AlgoLRU() {}

unsigned int AlgoLRU::selectPageToEvict() {
    unsigned int pageToEvict = this->pages.front();
    this->pages.pop_front();
    return pageToEvict;
}

void AlgoLRU::notifyAccess(unsigned int pageIndex) {
    this->pages.remove(pageIndex);
    this->pages.push_back(pageIndex);
}
