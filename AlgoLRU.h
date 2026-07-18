#ifndef ALGOLRU_H
#define ALGOLRU_H
#include "IPagingAlgorithm.h"
#include "list"

class AlgoLRU : public IPagingAlgorithm{

private:
    std::list<unsigned int> pages;

public:
    AlgoLRU();

    unsigned int selectPageToEvict();
    void notifyAccess(unsigned int pageIndex);
};

#endif // ALGOLRU_H
