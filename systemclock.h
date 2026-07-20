#ifndef SYSTEMCLOCK_H
#define SYSTEMCLOCK_H

/**
 * @brief Verwaltet die globale Systemzeit der Simulationsumgebung.
 *
 * Dient als Zeitbasis zur Messung und Evaluation der gesammelten
 * Latenzzeiten (z.B. für TLB-Hits, TLB-Misses und Page Faults).
 */
class SystemClock {

private:
    unsigned long currentTime = 0; // Der aktuelle simulierte Zeitstempel (z.B. in Taktzyklen).

public:
    /**
     * @brief Konstruktor der SystemClock-Klasse.
     *
     * Initialisiert die globale Systemzeit mit dem Startwert 0.
     */
    SystemClock();

    /**
     * @brief Addiert eine Latenz zur globalen Systemzeit hinzu.
     *
     * @param t Die hinzuzufügende Latenzzeit.
     */
    void addTime(unsigned int t) {
        this->currentTime += t;
    }

    /**
     * @brief Liefert den aktuellen Zeitstempel der Simulation zurück.
     *
     * @return Die aktuelle Systemzeit.
     */
    unsigned long getTime() const {
        return this->currentTime;
    }
};

#endif // SYSTEMCLOCK_H
