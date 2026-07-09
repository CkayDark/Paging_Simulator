#ifndef MEMORYCONSTANTS_H
#define MEMORYCONSTANTS_H


namespace MemoryConfig {

    static constexpr unsigned int RAM_SIZE = 1048576;
    static constexpr unsigned int PAGE_SIZE = 1024;
    static constexpr unsigned int VIRTUAL_MEMORY_SIZE = 16777216;
    static constexpr unsigned int PAGE_NUM = VIRTUAL_MEMORY_SIZE/PAGE_SIZE;
    static constexpr unsigned int PAGE_FRAME_SIZE = 1024;
    static constexpr unsigned int PAGE_FRAME_NUM = RAM_SIZE/PAGE_FRAME_SIZE;
    static constexpr unsigned int FRAME_TLB_FLAG = 0x01;
    static constexpr unsigned int FRAME_REFERENCED = 0x02;
}

namespace Latency {

    static constexpr unsigned int TLB_HIT = 1;
    static constexpr unsigned int TLB_MISS = 10;
    static constexpr unsigned int PAGE_FAULT = 1000;
}





#endif // MEMORYCONSTANTS_H
