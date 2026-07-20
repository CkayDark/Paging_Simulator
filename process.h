#ifndef PROCESS_H
#define PROCESS_H
#include "pagetable.h"

/**
 * @brief Repräsentiert einen Prozess innerhalb der Simulationsumgebung.
 *
 * Jeder Prozess besitzt eine eindeutige process_id und eine eigene
 * PageTable zur autonomen Verwaltung seines virtuellen Adressraums.
 */
class Process  {

private:
    unsigned char process_id;     // Eindeutige ID des Prozesses.
    PageTable* page_table;        // Zeiger auf die prozessspezifische Seitentabelle.

public:
    /**
     * @brief Konstruktor der Process-Klasse.
     *
     * Allokiert und initialisiert eine neue prozessspezifische Seitentabelle.
     */
    Process();

    /**
     * @brief Liefert den Zeiger auf die Seitentabelle dieses Prozesses zurück.
     *
     * @return Ein Zeiger auf das zugehörige PageTable-Objekt.
     */
    PageTable *getPage_table() const;
};

#endif // PROCESS_H
