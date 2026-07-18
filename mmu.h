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
#include "ram.h"
#include "IPagingAlgorithm.h"
#include "iostream"

class MMU
{

private:
    TLB* tlb;
    Process* process;
    SystemClock* clock;
    unsigned int next_tlb_victim;
    unsigned int pageIndex;
    RAM* ram;
    IPagingAlgorithm* algo;

public:
    MMU(SystemClock* c, RAM* ram, IPagingAlgorithm* algo);

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

    /**
     * @brief Übersetzt eine virtuelle Adresse in eine physische Adresse.
     *
     * Führt die Adressübersetzung in drei Stufen aus:
     * 1. TLB-Lookup (Fast Path): Bei Treffer direkte Adressberechnung.
     * 2. Page-Table-Lookup (TLB-Miss): Prüft, ob die Seite im RAM präsent ist,
     *    und aktualisiert ggf. den TLB.
     * 3. Page Fault (RAM-Miss): Lädt die Seite von Platte. Falls der RAM voll ist,
     *    wird über den Paging-Algorithmus eine Seite verdrängt (Eviction) und
     *    die TLB-Konsistenz gewahrt.
     *
     * @param virtual_address Die zu übersetzende virtuelle Adresse.
     * @param is_write Schreibzugriff oder Lesezugriff?
     * @return Die berechnete physische Adresse oder -1 bei Fehlern.
     */
    unsigned int translate(unsigned int virtual_address, bool is_write = false);

    /**
     * @brief Ermittelt den nächsten zu ersetzenden Index im TLB-Cache.
     *
     * Implementiert einen Ringzähler (Round-Robin), um bei einem TLB-Miss
     * den ältesten Eintrag im TLB-Array als Opfer auszuwählen. Der interne Zähler
     * wird dabei für den nächsten Aufruf zyklisch inkrementiert.
     *
     * @return Der Index des zu überschreibenden TLB-Eintrags.
     */
    int findTlbReplacementIndex();

    /**
     * @brief Gibt den virtuellen Seitenindex der letzten Adressübersetzung zurück.
     *
     * @return Der zuletzt berechnete virtuelle Seitenindex.
     */
    unsigned int getLastPageIndex() const;

    /**
    * @brief Durchsucht den TLB nach einem gültigen Eintrag für die gesuchte virtuelle Seite.
    *
    * @param page_index Der zu suchende virtuelle Seitenindex (VPN).
    * @return int Der zugehörige physische Frame-Index bei einem TLB-Hit, sonst -1 bei einem TLB-Miss.
    */
    int checkTLB(unsigned int page_index);

    /**
    * @brief Aktualisiert den TLB mit einer neuen Adressübersetzung.
    *
    * Bestimmt über findTlbReplacementIndex den zu überschreibenden TLB-Eintrag,
    * trägt die neue Übersetzung ein und setzt das FRAME_TLB_FLAG.
    *
    * @param page_index Der virtuelle Seitenindex.
    * @param frame_index Der physische Frame-Index im RAM.
    * @param attributes Die zu kopierenden Zugriffs- und Kontrollattribute der Seite.
    */
    void updateTLB(unsigned int page_index
                   , unsigned int frame_index, unsigned int attributes);

    /**
     * @brief Ungültigmachen eines TLB-Eintrags für eine bestimmte virtuelle Seite.
     *
     * Durchsucht den TLB nach Einträgen, die mit dem übergebenen Seitenindex
     * übereinstimmen, löscht deren Gültigkeits-Flag (FRAME_TLB_FLAG).
     * Verhindert veraltete Einträge im TLB nach einer Seitenverdrängung.
     *
     * @param page_index Der virtuelle Seitenindex, der aus dem TLB entfernt werden soll.
     */
    void invalidateTLB(unsigned int page_index);


    void setProcess(Process* p) {this->process = p; }
};

#endif // MMU_H
