#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <QDebug>
#include <QMessageBox>
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QThread>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_Insert_button_clicked();

    void on_Return_button_clicked();

    void on_CreateFuel_button_clicked();

    void onFuelTimer();

    void FuelProduction();


private:
    Ui::MainWindow *ui;

    QStateMachine *OilRig_StateMachine;
    QState *HasOil;
    QState *NoOil;
    QState *FuelCreation;

    QTimer *Fuel_timer;
    QTimer *Progress_timer;

};
#endif // MAINWINDOW_H
