#ifndef TLB_H
#define TLB_H
#include "tlbentry.h"

/**
 * @brief Repräsentiert den Translation Lookaside Buffer (TLB).
 *
 * Fungiert als schneller Cache für virtuelle
 * Adressübersetzungen, um den Zugriff auf die Seitentabelle im RAM abzukürzen.
 */
class TLB {

private:
    TLBEntry** entries;        // Array von Zeigern auf die TLB-Einträge.
    unsigned int size;         // Die Gesamtanzahl der Einträge im TLB.

public:
    /**
     * @brief Konstruktor der TLB-Klasse.
     *
     * Allokiert das Array für den TLB und initialisiert alle Einträge
     * basierend auf der festgelegten TLB-Größe.
     */
    TLB();

    /**
     * @brief Liefert die Gesamtanzahl der Einträge des TLB zurück.
     *
     * @return Die Größe des TLB.
     */
    unsigned int getSize() const;

    /**
     * @brief Liefert das Array aller TLB-Einträge zurück.
     *
     * @return Ein Zeiger auf das Array von Zeigern auf TLBEntry-Objekte.
     */
    TLBEntry **getEntries() const;
};

#endif // TLB_H
