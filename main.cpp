#include "mainwindow.h"

#include <QApplication>
#include "simulator.h"
#include "event.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();




    Simulator simulator = Simulator();
    Event event1 = Event(1, 24.7, Event::PAGE_ACCESS);
    Event event2 = Event(2, 1.7, Event::MEMORY_WRITE);
    Event event3 = Event(3, 4.6, Event::PAGE_FAULT);
    simulator.addEvent(event1);
    simulator.addEvent(event2);
    simulator.addEvent(event3);

    simulator.run();



    return a.exec();


}
