#ifndef ALGONRU_H
#define ALGONRU_H

#include "IPagingAlgorithm.h"
#include "pagetable.h"
#include "memoryconstants.h"

class AlgoNRU : public IPagingAlgorithm{

private:
    PageTable* pagetable;
    unsigned int access_count;
    static constexpr unsigned int RESET_INTERVAL = 1000;

public:
    AlgoNRU(PageTable* pagetable);
    unsigned int selectPageToEvict();
    void notifyAccess(unsigned int pageIndex);
};

#endif // ALGONRU_H
