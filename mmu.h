#ifndef MMU_H
#define MMU_H
#include "tlb.h"
#include "process.h"
#include "pagetable.h"
#include "pagetableentry.h"
#include "process.h"
#include "memoryconstants.h"
#include "pagetableentry.h"
#include "systemclock.h"

class MMU
{

private:
    TLB* tlb;
    Process* process;
    SystemClock* clock;
    unsigned int next_tlb_victim;

public:
    MMU(SystemClock* c);

    ~MMU(){
        if(process->getPage_table() != nullptr){
            for(unsigned int i=0; i<process->getPage_table()->getSize(); i++){
                delete process->getPage_table()->getEntries()[i];
            }

            delete[] process->getPage_table()->getEntries();
            delete process->getPage_table();
        }


        if(tlb != nullptr){
            for(unsigned int i=0; i<tlb->getSize(); i++){
                delete tlb->getEntries()[i];
            }
            delete[] tlb->getEntries();
            delete tlb;
        }



        delete this->process;
    };

    unsigned int translate(unsigned int virtual_address);

    int findTlbReplacementIndex();
};

#endif // MMU_H
