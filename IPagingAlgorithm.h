#ifndef IPAGINGALGORITHM_H
#define IPAGINGALGORITHM_H

/**
 * @brief Abstrakte Schnittstelle für alle Seitenersetzungs-Algorithmen.
 *
 * Definiert die Schnittstelle, die jeder Verdrängungs-Algorithmus (z. B. FIFO, LRU, NRU)
 * implementieren muss, um in der Simulationsumgebung verwendet werden zu können.
 */
class IPagingAlgorithm {

public:
    virtual ~IPagingAlgorithm() = default;

    /**
     * @brief Wählt eine geladene virtuelle Seite zur Verdrängung aus dem RAM aus.
     *
     * Wird aufgerufen, wenn bei einem Page Fault kein freier Platz mehr im Hauptspeicher
     * existiert und eine Seite auf die Festplatte ausgelagert werden muss.
     *
     * @return Die virtuelle Seitennummer der zu verdrängenden Seite.
     */
    virtual unsigned int selectPageToEvict() = 0;


    /**
    * @brief Informiert den Algorithmus über den Zugriff auf eine virtuelle Seite.
    *
    * Wird von der MMU bei jedem erfolgreichen Adressübersetzungs-Zugriff
    * (TLB-Hit, PT-Hit, geladener Page-Fault) aufgerufen, damit der Algorithmus
    * seine internen Statistiken (z.B. Zeitstempel oder Zugriffszähler) pflegen kann.
    *
    * @param pageIndex Der Index der virtuellen Seite, auf die zugegriffen wurde.
    */
    virtual void notifyAccess(unsigned int pageIndex) = 0;

};


#endif // IPAGINGALGORITHM_H


