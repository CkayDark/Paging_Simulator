#include "mainwindow.h"

#include <QApplication>
#include "simulator.h"
#include "event.h"
#include "fifo.h"
#include "ram.h"
#include "iostream"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    auto clock = std::make_unique<SystemClock>();
    auto ram = std::make_unique<RAM>();

    //da interface, typ muss explizit angegeben werden
    std::unique_ptr<IPagingAlgorithm> algo = std::make_unique<FIFO>();

    auto mmu = std::make_unique<MMU>(clock.get(), ram.get(), algo.get());
    Process* test_process = new Process();
    mmu->setProcess(test_process);


    Simulator simulator = Simulator(mmu.get(), algo.get());


    simulator.run();



    return a.exec();


}
