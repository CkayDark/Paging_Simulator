#ifndef ALGONFU_NOAGING_H
#define ALGONFU_NOAGING_H
#include "vector"
#include "IPagingAlgorithm.h"
#include "pagetable.h"

class AlgoNFU_noAging : public IPagingAlgorithm{

private:
    std::vector<int> counterForEachPage;
    PageTable* pageTable;

public:
    AlgoNFU_noAging(PageTable* pageTable);

    unsigned int selectPageToEvict();
    void notifyAccess(unsigned int pageIndex);
};

#endif // ALGONFU_NOAGING_H
