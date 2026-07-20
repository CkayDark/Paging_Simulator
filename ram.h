#ifndef RAM_H
#define RAM_H
#include <vector>

/**
 * @brief Repräsentiert den physischen Arbeitsspeicher (RAM) der Simulationsumgebung.
 *
 * Verwaltet ein Array physischer Page Frames und protokolliert, welche virtuelle
 * Seitennummer aktuell in welchem physischen Frame geladen ist.
 */
class RAM {

private:
    std::vector<int> frames; // Speichert pro Frame-Index die geladene virtuelle Seite (-1 wenn frei).

public:
    /**
     * @brief Konstruktor der RAM-Klasse.
     *
     * Initialisiert alle physischen Frames mit dem Wert -1 (Speicher ist leer).
     */
    RAM();

    /**
     * @brief Sucht nach dem ersten unbelegten physischen Frame im RAM.
     *
     * @return Der physische Index des freien Frames, oder -1, falls der RAM komplett belegt ist.
     */
    int findFreeFrame();

    /**
     * @brief Belegt einen bestimmten physischen Frame mit einer virtuellen Seite.
     *
     * @param frame_index Der physische Index des Frames im RAM.
     * @param page_index Der virtuelle Seitenindex, der in diesen Frame abgebildet wird.
     */
    void mapFrame(int frame_index, int page_index);

    /**
     * @brief Gibt einen belegten physischen Frame im RAM wieder frei.
     *
     * Setzt die Belegung des entsprechenden Frames zurück auf den Wert -1.
     *
     * @param frame Der physische Index des freizugebenden Frames.
     */
    void freeFrame(int frame);

    /**
     * @brief Liefert die virtuelle Seitennummer zurück, die aktuell in einem bestimmten Frame liegt.
     *
     * @param frame_index Der abzufragende physische Frame-Index im RAM.
     * @return Die geladene virtuelle Seitennummer, oder -1, falls der Frame leer ist.
     */
    int getPageInFrame(int frame_index) const;

    /**
     * @brief Liefert die Gesamtanzahl der physischen Frames im RAM zurück.
     *
     * @return Die Gesamtanzahl der Frames.
     */
    int getSize() const;

};

#endif // RAM_H
