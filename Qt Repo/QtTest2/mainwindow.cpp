#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_inspector.h"

#include "iostream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow),
    uiInspector(new Ui::Inspector)
{
    uiMainWindow->setupUi(this);

    // EmptyWidget
    QWidget* inspector = new QWidget();
    // Setup UI
    uiInspector->setupUi(inspector);
    // Put inspector in widget
    uiMainWindow->Inspector->setWidget(inspector);

    connect(uiMainWindow->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiInspector;
}


void MainWindow::openProject(){
    std::cout <<"OpenProject" << std::endl;
}

void MainWindow::saveProject(){
    std::cout <<"Save Project" << std::endl;
}
