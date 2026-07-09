#ifndef IPAGINGALGORITHM_H
#define IPAGINGALGORITHM_H


class IPagingAlgorithm {

public:
    virtual ~IPagingAlgorithm() = default;

    virtual unsigned int selectPageToEvict() = 0;

    virtual void notifyAccess(unsigned int pageIndex) = 0;

};











#endif // IPAGINGALGORITHM_H


