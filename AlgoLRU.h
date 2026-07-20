#ifndef ALGOLRU_H
#define ALGOLRU_H
#include "IPagingAlgorithm.h"
#include "list"

class AlgoLRU : public IPagingAlgorithm{

private:
    /**
     * @brief Liste zur Priorisierung der geladenen Seiten nach dem LRU-Prinzip.
     *
     * Neu zugegriffene Seiten werden hinten angehängt (Most Recently Used).
     * Die am längsten unbenutzte Seite steht stets ganz vorne (Least Recently Used)
     * und ist der nächste Kandidat für eine Verdrängung.
     */
    std::list<unsigned int> pages;


public:
    /**
     * @brief Konstruktor der AlgoLRU-Klasse.
     */
    AlgoLRU();

    /**
     * @brief Wählt die am längsten ungenutzte Seite (Least Recently Used) für die Verdrängung aus.
     *
     * Entfernt das vorderste Element der Liste und gibt dessen Seitennummer zurück.
     *
     * @return Die virtuelle Seitennummer der zu verdrängenden Seite.
     */
    unsigned int selectPageToEvict();

    /**
     * @brief Registriert einen Zugriff auf eine virtuelle Seite und aktualisiert deren LRU-Status.
     *
     * Sucht und entfernt die Seite aus ihrer bisherigen Position in der Liste
     * und fügt sie am Ende neu an, um sie als "Most Recently Used" zu kennzeichnen.
     *
     * @param pageIndex Der Index der virtuellen Seite, auf die zugegriffen wird.
     */
    void notifyAccess(unsigned int pageIndex);
};

#endif // ALGOLRU_H
