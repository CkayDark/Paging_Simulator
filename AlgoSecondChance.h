#ifndef ALGOSECONDCHANCE_H
#define ALGOSECONDCHANCE_H
#include "IPagingAlgorithm.h"
#include "queue"
#include "pagetable.h"
#include "vector"


class AlgoSecondChance : public IPagingAlgorithm {

private:
    /**
     * @brief Warteschlange zur Speicherung der geladenen virtuellen Seiten.
     *
     * Hält die exakte Reihenfolge der RAM-Belegung fest. Die älteste geladene
     * Seite steht stets ganz vorne (front) und wird als Erste für die
     * Verdrängung geprüft (First-In-First-Out-Reihenfolge).
     */
    std::queue<unsigned int> pages;

    /**
     * @brief Schnelles Lookup-Register zur Prüfung der RAM-Präsenz.
     *
     * Ermöglicht eine Prüfung in O(1)-Zeit, ob eine virtuelle Seitennummer
     * bereits in der `pages`-Warteschlange (und damit im RAM) existiert.
     * Verhindert doppelte Einträge bei wiederholten Zugriffen (Hits).
     */
    std::vector<bool> in_queue;

    /**
     * @brief Zeiger auf die Seitentabelle des Prozesses.
     *
     * Ermöglicht das Auslesen und Zurücksetzen des Referenz-Flags (FRAME_REFERENCED)
     * einer Seite, um zu entscheiden, ob diese eine zweite Chance erhält.
     */
    PageTable* pageTable;


public:
    /**
     * @brief Konstruktor der AlgoSecondChance-Klasse.
     *
     * Initialisiert das Lookup-Register auf die maximale Anzahl virtueller Seiten.
     *
     * @param pageTable Zeiger auf die Seitentabelle des laufenden Prozesses.
     */
    AlgoSecondChance(PageTable* pageTable);

    /**
     * @brief Wählt eine Seite nach dem Second-Chance-Verfahren zur Verdrängung aus.
     *
     * Prüft die älteste Seite ganz vorne in der Warteschlange. Ist ihr Referenz-Flag
     * (FRAME_REFERENCED) gesetzt, wird dieses auf 0 gesetzt und die Seite hinten neu
     * angehängt (Zweite Chance). Dies wird so lange wiederholt, bis eine Seite mit dem
     * Referenz-Flag 0 gefunden, aus der Warteschlange entfernt und verdrängt wird.
     *
     * @return Die virtuelle Seitennummer der zu verdrängenden Seite.
     */
    unsigned int selectPageToEvict();

    /**
     * @brief Registriert den Zugriff auf eine virtuelle Seite.
     *
     * Falls die Seite noch nicht im RAM liegt, wird sie hinten an die Warteschlange
     * angehängt und im Lookup-Register als aktiv markiert. Wiederholte Zugriffe (Hits)
     * auf bereits geladene Seiten werden ignoriert, da deren Bewertung über das
     * Referenz-Flag der Seitentabelle abgewickelt wird.
     *
     * @param pageIndex Der Index der virtuellen Seite, auf die zugegriffen wird.
     */
    void notifyAccess(unsigned int pageIndex);

};

#endif // ALGOSECONDCHANCE_H
