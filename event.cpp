#include "event.h"

Event::Event(int id, double timestamp, Type t, unsigned int virtualAddress)
    : ID(id), timestamp(timestamp), type(t), virtualAddress(virtualAddress) {
}

unsigned int Event::getVirtualAddress() const {
    return virtualAddress;
}
