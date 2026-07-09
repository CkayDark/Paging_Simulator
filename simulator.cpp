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

        if(currentEvent.getType() == Event::PAGE_ACCESS){
            unsigned int physicalAdress
                = this->mmu->translate(currentEvent.getVirtualAddress());
        }

        std::cout << "ID: "<< this->events.top().getID()
                  << " Timestamp: " << this->events.top().getTimestamp()
                  << " Type: " << this->events.top().getType() << std::endl;
        this->events.pop();
    }
}

void Simulator::addEvent(const Event &event) {
    this->events.push(event);
}
