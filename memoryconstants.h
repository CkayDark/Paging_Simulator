#ifndef MEMORYCONSTANTS_H
#define MEMORYCONSTANTS_H

/**
 * @namespace MemoryConfig
 * @brief Enthält alle globalen Konfigurationswerte und Flags für die Speicherverwaltung.
 */
namespace MemoryConfig {

    static constexpr unsigned int RAM_SIZE = 1048576;
    static constexpr unsigned int PAGE_SIZE = 1024;
    static constexpr unsigned int VIRTUAL_MEMORY_SIZE = 16777216;
    static constexpr unsigned int PAGE_NUM = VIRTUAL_MEMORY_SIZE/PAGE_SIZE;
    static constexpr unsigned int PAGE_FRAME_SIZE = 1024;
    static constexpr unsigned int PAGE_FRAME_NUM = RAM_SIZE/PAGE_FRAME_SIZE;

    // Flags

    /** @brief Flag zur Kennzeichnung, dass ein Eintrag im TLB gültig ist. */
    static constexpr unsigned int FRAME_TLB_FLAG = 0x01;

    /** @brief Referenz-Flag. Zeigt an, ob auf die Seite kürzlich zugegriffen wurde. */
    static constexpr unsigned int FRAME_REFERENCED = 0x02;

    /** @brief Present-Flag. Zeigt an, ob sich die Seite aktuell im physischen RAM befindet. */
    static constexpr unsigned int FRAME_PRESENT = 0x04;
}


/**
 * @brief Definiert die Latenzzeiten (in Zeiteinheiten/Taktzyklen)
 * für verschiedene Speicherereignisse.
 */
namespace Latency {

    /**
     * @brief Latenzzeit bei einem TLB-Treffer (Hit).
     * Sehr schneller, direkter Hardware-Zugriff.
     */
    static constexpr unsigned int TLB_HIT = 1;

    /**
     * @brief Latenzzeit bei einem TLB-Miss, wenn die Seite im RAM liegt.
     * Erfordert das Durchsuchen der Seitentabelle (Page Table Walk).
     */
    static constexpr unsigned int TLB_MISS = 10;

    /**
     * @brief Latenzzeit bei einem Seitenfehler (Page Fault).
     * Beinhaltet den zeitaufwendigen Festplattenzugriff zum Nachladen einer Seite.
     */
    static constexpr unsigned int PAGE_FAULT = 1000;

}



#endif // MEMORYCONSTANTS_H
