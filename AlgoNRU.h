#ifndef ALGONRU_H
#define ALGONRU_H

#include "IPagingAlgorithm.h"
#include "pagetable.h"

class AlgoNRU : public IPagingAlgorithm{

private:
    /**
     * @brief Zeiger auf die Seitentabelle des Prozesses.
     *
     * Ermöglicht das Prüfen geladener Seiten (FRAME_PRESENT) sowie das Auslesen und
     * Modifizieren der Referenz- (FRAME_REFERENCED) und Modified-Flags (FRAME_MODIFIED)
     * für die NRU-Klassifizierung.
     */
    PageTable* pagetable;

    /**
     * @brief Zugriffszähler zur Steuerung des periodischen Resets der Referenz-Bits.
     *
     * Zählt die Speicherzugriffe und setzt bei Erreichen des RESET_INTERVAL das
     * Referenz-Flag bei allen Seiten zurück.
     */
    unsigned int access_count;

    /**
     * @brief Schwellenwert der Speicherzugriffe, nach dem die Referenz-Bits aller Seiten gelöscht werden.
     */
    static constexpr unsigned int RESET_INTERVAL = 1000;

public:
    /**
     * @brief Konstruktor der AlgoNRU-Klasse.
     *
     * @param pagetable Zeiger auf die Seitentabelle des laufenden Prozesses.
     */
    AlgoNRU(PageTable* pagetable);

    /**
     * @brief Wählt eine Seite nach dem NRU-Verfahren (Not Recently Used) für die Verdrängung aus.
     *
     * Teilt alle im RAM präsenten Seiten (FRAME_PRESENT) anhand ihrer Referenz- und
     * Modified-Bits in vier Prioritätsklassen (Klasse 0 bis 3) ein. Wählt anschließend
     * die älteste bzw. am wenigsten genutzte Klasse und gibt die Seitennummer der
     * ersten passenden Seite zurück.
     *
     * @return Die virtuelle Seitennummer der zu verdrängenden Seite.
     */
    unsigned int selectPageToEvict();

    /**
     * @brief Registriert einen Speicherzugriff und setzt periodisch alle Referenz-Flags zurück.
     *
     * Erhöht den Zugriffszähler. Wird das RESET_INTERVAL erreicht, werden alle
     * Referenz-Flags (FRAME_REFERENCED) in der Seitentabelle zurückgesetzt, um das
     * Zeitfenster für "kürzlich genutzte Seiten" neu zu starten.
     *
     * @param pageIndex Der Index der virtuellen Seite, auf die zugegriffen wird.
     */
    void notifyAccess(unsigned int pageIndex);
};

#endif // ALGONRU_H
