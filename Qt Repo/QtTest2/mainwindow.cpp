#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_inspector.h"

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
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiInspector;
}
