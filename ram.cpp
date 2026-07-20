#include "ram.h"
#include "memoryconstants.h"

RAM::RAM() {
    this->frames.resize(MemoryConfig::PAGE_FRAME_NUM, -1);
}

//wenn freier Frame gefunden, gib Index aus
//wenn kein freier Frame, gib -1 aus
int RAM::findFreeFrame() {

    for(size_t i=0; i<this->frames.size(); i++){
        if(this->frames.at(i) == -1){
            return i;
        }
    }
    return -1;
}


void RAM::mapFrame(int frame_index, int page_index) {
    this->frames[frame_index] = page_index;
}

void RAM::freeFrame(int frame) {
    this->frames[frame] = -1;
}

int RAM::getPageInFrame(int frame_index) const {
    return this->frames[frame_index];
}

int RAM::getSize() const {
    return this->frames.size();
}
