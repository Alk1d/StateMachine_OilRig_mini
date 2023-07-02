#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OilRig_StateMachine = new QStateMachine(this);

    HasOil = new QState();
    NoOil = new QState();
    FuelCreation = new QState();

    Fuel_timer = new QTimer();
    Progress_timer = new QTimer();
    connect(Fuel_timer, SIGNAL(timeout()), this, SLOT(onFuelTimer()));

    OilRig_StateMachine->addState(HasOil);
    OilRig_StateMachine->addState(NoOil);
    OilRig_StateMachine->addState(FuelCreation);
    OilRig_StateMachine->setInitialState(NoOil);
    OilRig_StateMachine->start();

    NoOil->assignProperty(ui->State_label, "text", "No Oil");
    NoOil->assignProperty(ui->CurrentState_label, "text", "No Oil");
    NoOil->addTransition(ui->Insert_button, &QPushButton::clicked, HasOil);

    HasOil->assignProperty(ui->State_label, "text", "Has Oil");
    HasOil->assignProperty(ui->CurrentState_label, "text", "Has Oil");
    HasOil->addTransition(ui->CreateFuel_button, &QPushButton::clicked, FuelCreation);
    HasOil->addTransition(ui->Return_button, &QPushButton::clicked, NoOil);

    FuelCreation->assignProperty(ui->State_label, "text", "Fuel creation");
    FuelCreation->assignProperty(ui->CurrentState_label, "text", "Fuel creation");
    FuelCreation->addTransition(Progress_timer, &QTimer::timeout, NoOil);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Insert_button_clicked()
{

    if (OilRig_StateMachine->configuration().contains(HasOil))
        ui->State_label->setText("Already full!");
    if (OilRig_StateMachine->configuration().contains(FuelCreation))
        ui->State_label->setText("Creating fuel, wait!");
   return;
}


void MainWindow::on_Return_button_clicked()
{
    if (OilRig_StateMachine->configuration().contains(NoOil))
        ui->State_label->setText("Nothing to return!");
    if (OilRig_StateMachine->configuration().contains(FuelCreation))
        ui->State_label->setText("Creating fuel, wait!");
    return;
}


void MainWindow::on_CreateFuel_button_clicked()
{
    if (OilRig_StateMachine->configuration().contains(NoOil))
        ui->State_label->setText("No oil to create fuel!");
    if (OilRig_StateMachine->configuration().contains(HasOil))
        FuelProduction();
    return;
}




void MainWindow::onFuelTimer()
{
    if (ui->progressBar->value() > 99)
    {
        ui->progressBar->setValue(1);
        Fuel_timer->stop();
        return;
    }
    ui->progressBar->setValue(ui->progressBar->value()+1);
}

void MainWindow::FuelProduction()
{
    int time = 10;
    Fuel_timer->start(time);
    Progress_timer->start(time*99);
}




