#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "event.h"
#include <queue>
#include "mmu.h"
#include "IPagingAlgorithm.h"

/**
 * @brief Zentraler Diskrete-Ereignis-Simulator (DES) für das Paging-System.
 *
 * Verwaltet eine chronologisch sortierte Ereigniswarteschlange (Priority Queue)
 * und steuert die schrittweise Ausführung aller Speicherereignisse über die MMU.
 */
class Simulator {

private:
    std::priority_queue<Event> events;  // Chronologische Warteschlange (Min-Heap) der anstehenden Simulationsereignisse.
    MMU* mmu;                           // Zeiger auf die Memory Management Unit des Simulators.
    IPagingAlgorithm* algo;             // Zeiger auf den zu evaluierenden Seitenersetzungs-Algorithmus.

public:
    /**
     * @brief Konstruktor der Simulator-Klasse.
     *
     * Verknüpft den Simulator mit der MMU und dem zu testenden Algorithmus.
     *
     * @param mmu Zeiger auf die konfigurierte MMU.
     * @param algo Zeiger auf die Instanz des zu evaluierenden Paging-Algorithmus.
     */
    Simulator(MMU* mmu, IPagingAlgorithm* algo);

    /**
     * @brief Startet den Simulationslauf.
     *
     * Entnimmt nacheinander alle Ereignisse aus der chronologischen Warteschlange.
     */
    void run();

    /**
     * @brief Fügt der Simulationsumgebung ein neues Ereignis hinzu.
     *
     * Das Ereignis wird automatisch anhand seines Zeitstempels an der chronologisch
     * korrekten Position in der Prioritätswarteschlange einsortiert.
     *
     * @param event Das in die Simulation einzufügende Ereignis-Objekt.
     */
    void addEvent(const Event& event);

    /**
     * @brief Liefert den Zeiger auf die MMU des Simulators zurück.
     *
     * @return Ein Zeiger auf das zugehörige MMU-Objekt.
     */
    MMU *getMmu() const;
};

#endif // SIMULATOR_H
