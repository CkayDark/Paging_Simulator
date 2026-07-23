#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "event.h"
#include "IPagingAlgorithm.h"
#include "process.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief Generiert eine Liste von Speicherzugriffs-Ereignissen für den Benchmark.
     *
     * Erzeugt Test-Events (Sowohl Lese- als auch Schreibzugriffe) mit zeitlicher
     * und räumlicher Lokalität, um realistische Zugriffsstrukturen zu simulieren.
     *
     * @return Ein Vektor mit den generierten Ereignissen.
     */
    std::vector<Event> generateEventList();

    /**
     * @brief Führt einen einzelnen Simulationsdurchlauf für einen bestimmten Algorithmus aus.
     *
     * Instanziiert die benötigte Simulations-Infrastruktur (SystemClock, RAM, MMU, Simulator),
     * verarbeitet die übergebene Ereignisliste und gibt die gemessene Gesamtzeit zurück.
     * Gibt am Ende alle für diesen Durchlauf erstellten Ressourcen wieder frei.
     *
     * @param algo Der zu evaluierende Seitenersetzungs-Algorithmus.
     * @param process Der für diesen Durchlauf erstellte Testprozess.
     * @param events Die zu verarbeitende Referenzliste von Speicherereignissen.
     * @return Ein formatierter Ergebnis-String mit der gemessenen Gesamtdauer der Simulation.
     */
    QString runSimulation(IPagingAlgorithm *algo, Process* process, const std::vector<Event>& events);

private slots:
    /**
     * @brief Slot-Methode, die beim Klicken auf den RUN-Button ausgelöst wird.
     *
     * Initialisiert den Zufallsgenerator, erzeugt die Test-Events, führt alle sechs
     * Algorithmen nacheinander auf derselben Datenbasis aus und gibt den vergleichenden
     * Abschlussbericht im Textfeld aus.
     */
    void on_pushButton_RUN_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
