#ifndef ALGOFIFO_H
#define ALGOFIFO_H
#include "IPagingAlgorithm.h"
#include "queue"

class AlgoFifo : public IPagingAlgorithm {

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


public:

    /**
     * @brief Konstruktor der AlgoFifo-Klasse.
     *
     * Initialisiert das interne Lookup-Register (in_queue) auf die maximale
     * Anzahl virtueller Seiten, um Zugriffe ohne Out-of-Bounds-Fehler prüfen zu können.
     */
    AlgoFifo();

    /**
     * @brief Registriert den Zugriff auf eine virtuelle Seite im FIFO-Verfahren.
     *
     * Falls die Seite noch nicht im RAM liegt, wird sie hinten an die Warteschlange
     * angehängt und im Lookup-Register als aktiv markiert. Wiederholte Zugriffe (Hits)
     * werden ignoriert, um die ursprüngliche FIFO-Reihenfolge nicht zu beeinflussen.
     *
     * @param pageIndex Der Index der virtuellen Seite, auf die zugegriffen wird.
     */
    void notifyAccess(unsigned int pageIndex);

    /**
     * @brief Wählt die am längsten geladene virtuelle Seite für die Verdrängung aus.
     *
     * Liest die vorderste Seite der Warteschlange aus, entfernt sie und setzt
     * deren Status im Lookup-Register zurück auf inaktiv.
     *
     * @return Die virtuelle Seitennummer der zu verdrängenden Seite.
     */
    unsigned int selectPageToEvict();

};

#endif // ALGOFIFO_H
