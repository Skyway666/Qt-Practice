#include "mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"
#include "sceneview.h"

#include "ui_mainwindow.h"

#include "iostream"

#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);

    connect(uiMainWindow->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

    hierarchy = new Hierarchy();
    uiMainWindow->Hierarchy->setWidget(hierarchy);

    inspector = new Inspector();
    uiMainWindow->Inspector->setWidget(inspector);

    scene = new SceneView();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(scene);
    uiMainWindow->centralWidget->setLayout(layout);

    connect(hierarchy, SIGNAL(entityChanged(int)), inspector, SLOT(onEntityChanged(int)));
    connect(hierarchy, SIGNAL(entityCreated()), scene, SLOT(onEntityCreated()));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}


void MainWindow::openProject(){


    QMessageBox::StandardButton button = QMessageBox::question(this, "Pregunta importante", "Eres tonto?");

    if(button == QMessageBox::Yes)
        std::cout <<"Ya lo sabia" << std::endl;
    else if(button == QMessageBox::No){
        std::cout <<"Que mentiroso..." << std::endl;
        return;
    }


    QString filepath = QFileDialog::getOpenFileName(this, "Load file");

    if(!filepath.isEmpty()){
        QMessageBox::information(this, "Path", filepath);
    }

}

void MainWindow::saveProject(){
    std::cout <<"Save Project" << std::endl;
}
