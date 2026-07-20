#ifndef ALGONFU_WITHAGING_H
#define ALGONFU_WITHAGING_H
#include "IPagingAlgorithm.h"
#include "pagetable.h"
#include "vector"

class AlgoNFU_withAging : public IPagingAlgorithm{

private:
    /**
     * @brief Zeiger auf die Seitentabelle des Prozesses.
     *
     * Erlaubt das Identifizieren geladener Seiten (FRAME_PRESENT) sowie das Auslesen
     * und Zurücksetzen der Referenz-Flags (FRAME_REFERENCED) für das Aging-Verfahren.
     */
    PageTable* pageTable;

    /**
     * @brief Bit-Register zur Speicherung des gealterten Zugriffswerts jeder virtuellen Seite.
     *
     * Die Zähler dienen als Schieberegister (Aging). Bei jedem Intervall-Reset werden sie
     * um 1 Bit nach rechts verschoben (Wert halbiert sich), um ältere Zugriffe abzuwerten.
     */
    std::vector<unsigned int> counterForEachPage;

    /**
     * @brief Zugriffszähler zur Steuerung des periodischen Alterungsprozesses.
     *
     * Erfasst die Anzahl der Speicherzugriffe und löst bei Erreichen des RESET_INTERVAL
     * das Bit-Shifting für alle virtuellen Seiten aus.
     */
    unsigned int access_count = 0;

    /**
     * @brief Schwellenwert der Speicherzugriffe, nach dem der Aging-Prozess ausgeführt wird.
     */
    static constexpr unsigned int RESET_INTERVAL = 1000;

public:
    /**
     * @brief Konstruktor der AlgoNFU_withAging-Klasse.
     *
     * Initialisiert alle Aging-Register mit dem Startwert 0.
     *
     * @param pageTable Zeiger auf die Seitentabelle des laufenden Prozesses.
     */
    AlgoNFU_withAging(PageTable* pageTable);

    /**
     * @brief Wählt die am seltensten und am längsten ungenutzte Seite für die Verdrängung aus.
     *
     * Durchsucht alle im RAM geladenen Seiten (FRAME_PRESENT) nach dem kleinsten
     * Wert im gealterten Bit-Register.
     *
     * @return Die virtuelle Seitennummer der zu verdrängenden Seite.
     */
    unsigned int selectPageToEvict();

    /**
     * @brief Registriert einen Zugriff auf eine virtuelle Seite und steuert das periodische Altern.
     *
     * Erhöht den Zugriffszähler. Bei Erreichen des RESET_INTERVAL werden die Zähler
     * aller Seiten halbiert (Shifting). Bei Seiten, die im letzten Intervall aktiv waren
     * (FRAME_REFERENCED), wird das höchste Bit gesetzt. Anschließend werden alle
     * Referenz-Flags in der Seitentabelle zurückgesetzt.
     *
     * @param pageIndex Der Index der virtuellen Seite, auf die zugegriffen wird.
     */
    void notifyAccess(unsigned int pageIndex);
};

#endif // ALGONFU_WITHAGING_H
