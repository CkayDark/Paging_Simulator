#ifndef RAM_H
#define RAM_H
#include <vector>
#include "memoryconstants.h"


class RAM {

private:
    std::vector<int> frames;


public:
    RAM();

    int findFreeFrame();
    void mapFrame(int frame_index, int page_index);
    void freeFrame(int frame);
    int getPageInFrame(int frame_index) const;
    int getSize() const;

};

#endif // RAM_H
