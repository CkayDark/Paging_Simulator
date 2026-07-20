#ifndef TLBENTRY_H
#define TLBENTRY_H

/**
 * @brief Repräsentiert einen einzelnen Eintrag im Translation Lookaside Buffer (TLB).
 *
 * Speichert eine aktive Abbildung einer virtuellen Seitennummer auf einen physischen
 * Page Frame im RAM sowie die dazugehörigen Statusattribute (Flags).
 */
class TLBEntry {

private:
    unsigned int page_index;              // Die im TLB-Eintrag hinterlegte virtuelle Seitennummer.
    unsigned int page_frame_index;        // Der zugehörige physische Frame-Index im Hauptspeicher.
    unsigned char frame_attributes;       // Status-Flags (z.B. FRAME_TLB_FLAG) des TLB-Eintrags.

public:
    /**
     * @brief Konstruktor der TLBEntry-Klasse.
     *
     * Initialisiert alle Indizes und Attribute auf den Standardwert 0.
     */
    TLBEntry();

    /**
     * @brief Liefert die Status-Flags (Attribute) des TLB-Eintrags zurück.
     *
     * @return Die Bitmaske der aktuellen Attribute.
     */
    unsigned char getFrame_attributes() const;

    /**
     * @brief Liefert den im TLB-Eintrag gespeicherten physischen Frame-Index zurück.
     *
     * @return Der physische Index im RAM.
     */
    unsigned int getPage_frame_index() const;

    /**
     * @brief Liefert die im TLB-Eintrag gespeicherte virtuelle Seitennummer zurück.
     *
     * @return Die virtuelle Seitennummer.
     */
    unsigned int getPage_index() const;

    /**
     * @brief Setzt die Status-Flags (Attribute) für diesen TLB-Eintrag.
     *
     * @param frame_attributes Die neue Bitmaske der Attribute.
     */
    void setFrame_attributes(unsigned char frame_attributes);

    /**
     * @brief Setzt den physischen Frame-Index für diesen TLB-Eintrag.
     *
     * @param pf_index Der neue physische Index im RAM.
     */
    void setPage_frame_index(unsigned int pf_index);

    /**
     * @brief Setzt die virtuelle Seitennummer für diesen TLB-Eintrag.
     *
     * @param p_index Die neue virtuelle Seitennummer.
     */
    void setPage_index(unsigned int p_index);
};

#endif // TLBENTRY_H
