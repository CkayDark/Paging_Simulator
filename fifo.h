#ifndef FIFO_H
#define FIFO_H
#include "IPagingAlgorithm.h"

class FIFO : public IPagingAlgorithm {
public:
    FIFO();
    void notifyAccess(unsigned int pageIndex);
};

#endif // FIFO_H
