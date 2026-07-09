#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "event.h"
#include <queue>
#include "mmu.h"
#include "IPagingAlgorithm.h"

class Simulator {


private:
    std::priority_queue<Event> events;

    MMU* mmu;

    IPagingAlgorithm* algo;


public:
    Simulator(MMU* mmu, IPagingAlgorithm* algo);

    void run();

    void addEvent(const Event& event);
    MMU *getMmu() const;
};



#endif // SIMULATOR_H
