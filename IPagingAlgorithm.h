#ifndef IPAGINGALGORITHM_H
#define IPAGINGALGORITHM_H


class IPagingAlgorithm {

public:
    virtual ~IPagingAlgorithm() = default;

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


