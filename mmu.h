#ifndef MMU_H
#define MMU_H
#include "tlb.h"
#include "process.h"
#include "process.h"
#include "systemclock.h"
#include "ram.h"
#include "IPagingAlgorithm.h"

/**
 * @brief Repräsentiert die Memory Management Unit (MMU) des Simulators.
 *
 * Steuert die Adressübersetzung von virtuellem zu physischem Speicher, verwaltet
 * den TLB-Cache und interagiert bei Fehlzugriffen mit dem physischen RAM und
 * den Paging-Algorithmen.
 */
class MMU {

private:
    TLB* tlb;                         // Zeiger auf den Translation Lookaside Buffer (TLB).
    Process* process;                 // Zeiger auf den aktuell geladenen Prozess.
    SystemClock* clock;               // Zeiger auf das globale Systemzeit-Objekt zur Zeitmessung.
    unsigned int next_tlb_victim;     // Index-Zeiger für das zyklische Ersetzen von TLB-Einträgen (FIFO).
    unsigned int pageIndex;           // Speichert den virtuellen index der letzten Übersetzung.
    RAM* ram;                         // Zeiger auf den simulierten physischen Hauptspeicher.
    IPagingAlgorithm* algo;           // Zeiger auf den aktuell aktiven Verdrängungs-Algorithmus.

public:
    /**
     * @brief Konstruktor der MMU-Klasse.
     *
     * Verknüpft die MMU mit der globalen Zeitbasis, dem RAM-Modell und dem
     * gewählten Paging-Algorithmus.
     *
     * @param c Zeiger auf das SystemClock-Objekt zur Latenz-Zeitmessung.
     * @param ram Zeiger auf den physischen Speicher zur Speicherplatzzuweisung.
     * @param algo Zeiger auf die Schnittstelle des aktiven Paging-Algorithmus.
     */
    MMU(SystemClock* c, RAM* ram, IPagingAlgorithm* algo);



    /**
     * @brief Übersetzt eine virtuelle Adresse in eine physische Adresse.
     *
     * Führt die Adressübersetzung in drei Stufen aus:
     * 1. TLB-Lookup (Fast Path): Bei Treffer direkte Adressberechnung.
     * 2. Page-Table-Lookup (TLB-Miss): Prüft, ob die Seite im RAM präsent ist,
     *    und aktualisiert ggf. den TLB.
     * 3. Page Fault (RAM-Miss): Lädt die Seite von Platte. Falls der RAM voll ist,
     *    wird über den Paging-Algorithmus eine Seite verdrängt (Eviction).
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

    /**
     * @brief Setzt den aktuell auszuführenden Prozess für die Adressübersetzung.
     *
     * @param p Zeiger auf den Prozess, dessen virtueller Adressraum übersetzt werden soll.
     */
    void setProcess(Process* p) {this->process = p; }
};

#endif // MMU_H
