#ifndef PAGETABLE_H
#define PAGETABLE_H
#include "pagetableentry.h"

/**
 * @brief Repräsentiert die Page Table eines Prozesses.
 *
 * Verwaltet ein Array von Seitentabelleneinträgen, um die Abbildung des gesamten
 * virtuellen Adressraums eines Prozesses auf den physischen RAM abzubilden.
 */
class PageTable {

private:
    PageTableEntry** entries;     // Array von Zeigern auf die Seitentabelleneinträge.
    unsigned int size;            // Gesamtanzahl der Einträge in der Seitentabelle.

public:
    /**
     * @brief Konstruktor der PageTable-Klasse.
     *
     * Allokiert das Array für die Seitentabelle und initialisiert alle Einträge
     * basierend auf der maximalen Seitenanzahl (MemoryConfig::PAGE_NUM).
     */
    PageTable();

    /**
     * @brief Liefert das Array aller Seitentabelleneinträge zurück.
     *
     * @return Ein Zeiger auf das Array von Zeigern auf PageTableEntry-Objekte.
     */
    PageTableEntry **getEntries() const;

    /**
     * @brief Liefert die Gesamtanzahl der Einträge in der Seitentabelle zurück.
     *
     * @return Die Größe der Seitentabelle.
     */
    unsigned int getSize() const;
};

#endif // PAGETABLE_H
