#ifndef ALGONFU_NOAGING_H
#define ALGONFU_NOAGING_H
#include "vector"
#include "IPagingAlgorithm.h"
#include "pagetable.h"

class AlgoNFU_noAging : public IPagingAlgorithm{

private:
    /**
     * @brief Software-Zähler für die Zugriffshäufigkeit aller virtuellen Seiten.
     *
     * Jede virtuelle Seite besitzt einen eigenen Zähler, der die Gesamtzahl
     * der Lese- und Schreibzugriffe speichert.
     */
    std::vector<int> counterForEachPage;

    /**
     * @brief Zeiger auf die Seitentabelle des Prozesses.
     *
     * Ermöglicht der Verdrängungs-Logik die Prüfung, welche virtuellen Seiten
     * aktuell physisch im RAM geladen sind (FRAME_PRESENT).
     */
    PageTable* pageTable;

public:
    /**
     * @brief Konstruktor der AlgoNFU_noAging-Klasse.
     *
     * Initialisiert die Zähler für alle virtuellen Seiten mit dem Startwert 0.
     *
     * @param pageTable Zeiger auf die Seitentabelle des laufenden Prozesses.
     */
    AlgoNFU_noAging(PageTable* pageTable);

    /**
     * @brief Wählt die am seltensten genutzte Seite (Not Frequently Used) für die Verdrängung aus.
     *
     * Durchsucht alle im RAM geladenen Seiten (FRAME_PRESENT) nach dem
     * kleinsten Zählerwert im Software-Register.
     *
     * @return Die virtuelle Seitennummer der zu verdrängenden Seite.
     */
    unsigned int selectPageToEvict();

    /**
     * @brief Registriert einen Zugriff auf eine virtuelle Seite und erhöht deren Zähler.
     *
     * Inkrementiert den Häufigkeitszähler der angesprochenen Seite um 1.
     *
     * @param pageIndex Der Index der virtuellen Seite, auf die zugegriffen wird.
     */
    void notifyAccess(unsigned int pageIndex);

};

#endif // ALGONFU_NOAGING_H
