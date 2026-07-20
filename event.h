#ifndef EVENT_H
#define EVENT_H

/**
 * @brief Repräsentiert ein diskretes Ereignis (Event) in der Simulationsumgebung.
 *
 * Jedes Ereignis speichert einen Ausführungszeitpunkt (Timestamp), eine eindeutige ID,
 * einen Ereignistyp (Type) und die betroffene virtuelle Adresse.
 */
class Event {

public:
    /**
     * @brief Definiert die verschiedenen Typen von Simulationsereignissen.
     */
    enum Type {
        PAGE_ACCESS,   // Regulärer virtueller Speicherzugriff (Lesezugriff).
        TLB_MISS,      // Fehlzugriff im TLB-Cache.
        PAGE_FAULT,    // Seitenfehler (Seite liegt nicht im physischen RAM).
        MEMORY_WRITE   // Speicherzugriff mit Schreiboperation (wichtig für das Modified-Bit).
    };

    /**
     * @brief Konstruktor der Event-Klasse.
     *
     * @param id Eindeutige ID des Ereignisses.
     * @param timestamp Zeitpunkt des Ereignisses auf der Simulations-Zeitachse.
     * @param t Der Typ des Ereignisses.
     * @param virtualAddress Die betroffene virtuelle Adresse im Adressraum des Prozesses.
     */
    Event(int id, double timestamp, Type t, unsigned int virtualAddress);

    /**
     * @brief Vergleichsoperator für die Prioritätswarteschlange (Min-Heap).
     *
     * Vergleicht die Zeitstempel zweier Ereignisse. Sorgt dafür, dass Ereignisse mit
     * kleinerem Zeitstempel zuerst verarbeitet werden.
     *
     * @param other Das andere Event zum Vergleich.
     * @return true, wenn dieses Event einen größeren Zeitstempel hat als other.
     */
    bool operator<(const Event& other) const {
        return this->timestamp > other.timestamp;
    }

    /**
     * @brief Liefert den Simulationszeitpunkt des Ereignisses.
     * @return Der Zeitstempel des Ereignisses.
     */
    double getTimestamp() const { return timestamp; }

    /**
     * @brief Liefert die eindeutige ID des Ereignisses.
     * @return Die ID des Ereignisses.
     */
    int getID() const { return ID; }

    /**
     * @brief Liefert den Typ des Ereignisses.
     * @return Der Event-Typ.
     */
    Type getType() const { return type; }

    /**
     * @brief Liefert die betroffene virtuelle Adresse des Ereignisses.
     * @return Die virtuelle Adresse.
     */
    unsigned int getVirtualAddress() const;

private:
    double timestamp;             // Zeitpunkt des Auftretens in der Simulationszeit.
    int ID;                       // Eindeutige Kennung des Ereignisses.
    Type type;                    // Typ des Ereignisses.
    unsigned int virtualAddress;  // Betroffene virtuelle Adresse.
};



#endif // EVENT_H
