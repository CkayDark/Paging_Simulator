#ifndef PAGETABLEENTRY_H
#define PAGETABLEENTRY_H

/**
 * @brief Repräsentiert einen Page Table Entry.
 *
 * Verwaltet den physischen Frame-Index im RAM sowie die Bitmaske der
 * Status- und Zugriffsattribute (Flags) für eine virtuelle Seite.
 */
class PageTableEntry {

private:
    unsigned int page_frame_index;        // Der physische Index des zugeordneten Page Frames im RAM.
    unsigned char frame_attributes;       // Status-Flags (z.B. Present, Referenced, Modified) als Bitmaske.

public:
    /**
     * @brief Konstruktor der PageTableEntry-Klasse.
     *
     * Initialisiert den Frame-Index auf 0 und setzt alle Attribute auf 0 (Seite ist inaktiv).
     */
    PageTableEntry();

    /**
     * @brief Liefert die Status-Flags (Attribute) des Eintrags zurück.
     *
     * @return Die Bitmaske der aktuellen Seitenattribute.
     */
    unsigned char getFrame_attributes() const;

    /**
     * @brief Liefert den zugeordneten physischen Frame-Index zurück.
     *
     * @return Der Frame-Index im physischen RAM.
     */
    unsigned int getPage_frame_index() const;

    /**
     * @brief Setzt den physischen Frame-Index für diesen Eintrag.
     *
     * @param newPage_frame_index Der neue Frame-Index im physischen Hauptspeicher.
     */
    void setPage_frame_index(unsigned int newPage_frame_index);

    /**
     * @brief Setzt die Status-Flags (Attribute) für diesen Eintrag.
     *
     * @param newFrame_attributes Die neue Bitmaske für die Status-Flags.
     */
    void setFrame_attributes(unsigned char newFrame_attributes);
};

#endif // PAGETABLEENTRY_H
