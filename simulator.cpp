#include "simulator.h"
#include <iostream>

MMU *Simulator::getMmu() const {
    return mmu;
}

Simulator::Simulator(MMU* mmu, IPagingAlgorithm* algo)
    : mmu(mmu), algo(algo) {
}

void Simulator::run() {

    while(!events.empty()){

        Event currentEvent = events.top();
        events.pop();

        int result = this->mmu->translate(currentEvent.getVirtualAddress());

        if(result == -1) {
            unsigned int faultingPageIndex = this->mmu->getLastPageIndex();

            unsigned int victimPage = this->algo->selectPageToEvict();

        }

    }
}

void Simulator::addEvent(const Event &event) {
    this->events.push(event);
}
