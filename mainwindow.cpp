#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "systemclock.h"
#include "ram.h"
#include "mmu.h"
#include "simulator.h"
#include "memoryconstants.h"
#include "vector"
#include "AlgoFifo.h"
#include "AlgoLRU.h"
#include "AlgoNFU.h"
#include "AlgoNFU_noaging.h"
#include "AlgoNFU_withaging.h"
#include "AlgoNRU.h"
#include "AlgoSecondChance.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

std::vector<Event> MainWindow::generateEventList() {
    std::vector<Event> eventList;

    for(int i=0; i<2000; i++){

        //event randomizen
        unsigned int id = i;
        double timestamp = id * 1.0;
        Event::Type type = Event::PAGE_ACCESS;
        int rand = std::rand() % 10;
        if(rand > 8){
            type = Event::MEMORY_WRITE;
        }
        unsigned int address;
        if(rand < 9){
            address = std::rand() % 20480;
        } else{
            address = std::rand() % MemoryConfig::VIRTUAL_MEMORY_SIZE;
        }

        eventList.push_back(Event(id,timestamp,type,address));
    }
    return eventList;
}

QString MainWindow::runSimulation(IPagingAlgorithm* algo, Process* process,
                                  const std::vector<Event>& events){
    SystemClock* clock = new SystemClock();
    RAM* ram = new RAM();
    MMU* mmu = new MMU(clock, ram, algo);
    mmu->setProcess(process);
    Simulator* simulator = new Simulator(mmu, algo);

    for(int i=0; i<events.size(); i++){
        simulator->addEvent(events.at(i));
    }

    simulator->run();
    QString log = QString::number(clock->getTime()) + "\n";

    delete clock;
    delete ram;
    delete mmu;
    delete process;
    delete simulator;
    delete algo;

    return log;
}


void MainWindow::on_pushButton_RUN_clicked() {

    srand(time(nullptr));

    std::vector<Event> events = generateEventList();

    QString finalReport = "--- SIMULATIONSERGEBNISSE --- \n\n";

    Process* p1 = new Process();
    IPagingAlgorithm* fifo = new AlgoFifo();
    finalReport += "FIFO: " + runSimulation(fifo, p1, events);

    Process* p2 = new Process();
    IPagingAlgorithm* lru = new AlgoLRU();
    finalReport += "LRU: " + runSimulation(lru, p2, events);

    Process* p3 = new Process();
    IPagingAlgorithm* nfu_NoAging = new AlgoNFU_noAging(p3->getPage_table());
    finalReport += "NFU (No Aging): "+runSimulation(nfu_NoAging, p3, events);

    Process* p4 = new Process();
    IPagingAlgorithm* nfu_WithAging = new AlgoNFU_withAging(p4->getPage_table());
    finalReport += "NFU (With Aging): " + runSimulation(nfu_WithAging, p4, events);

    Process* p5 = new Process();
    IPagingAlgorithm* nru = new AlgoNRU(p5->getPage_table());
    finalReport += "NRU: " + runSimulation(nru, p5, events);

    Process* p6 = new Process();
    IPagingAlgorithm* secondChance = new AlgoSecondChance(p6->getPage_table());
    finalReport += "Second Chance: " + runSimulation(secondChance, p6, events);


    ui->textEdit->setText(finalReport);
}

