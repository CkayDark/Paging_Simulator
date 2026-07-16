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
    AlgoFifo();
    void notifyAccess(unsigned int pageIndex);
    unsigned int selectPageToEvict();

};

#endif // ALGOFIFO_H
