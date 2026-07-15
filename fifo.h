#ifndef FIFO_H
#define FIFO_H
#include "IPagingAlgorithm.h"
#include "queue"

class FIFO : public IPagingAlgorithm {

private:
    std::queue<unsigned int> pages;
    std::vector<bool> in_queue;


public:
    FIFO();

    void notifyAccess(unsigned int pageIndex);
    unsigned int selectPageToEvict();

};

#endif // FIFO_H
