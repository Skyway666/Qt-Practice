#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Enter, SIGNAL(clicked()), this, SLOT(EnterButton_Callback1()));
    connect(ui->Exit, SIGNAL(clicked()), this, SLOT(ExitButton_Callback1()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EnterButton_Callback1(){

    ui->text->setText("Entering...");
}
void MainWindow::ExitButton_Callback1(){
    ui->text->setText("Exiting...");
}
