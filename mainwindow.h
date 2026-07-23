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

    std::vector<Event> generateEventList();

    QString runSimulation(IPagingAlgorithm *algo, Process* process, const std::vector<Event>& events);
private slots:
    void on_pushButton_RUN_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
